#include <executor/sshconnection.h>

#include <libssh2.h>
#include <mutex>
#include <utility>

#ifndef WIN32
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

namespace {

std::once_flag sockets_initialized;
std::once_flag libssh2_initialized;

    bool initializeSockets() {
#ifdef WIN32
    WSADATA wsadata;
    int err;

    err = WSAStartup(MAKEWORD(2, 0), &wsadata);
    if(err != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", err);
        throw std::runtime_error("WSAStartup failed");
    }
#endif
    return true;

    }

    void close_socket(libssh2_socket_t sock) {
#ifdef WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    }
}

SSHConnection::SSHConnection(
    std::string server,
    std::string path,
    std::string username,

    authentication_t auth_type,
    std::string password,

    std::string pubkey_file,
    std::string privkey_file,
    std::string privkey_password
        ):
    server(server),
    path(std::move(path)),
    username(std::move(username)),
    auth_type(auth_type),
    password(std::move(password)),
    pubkey_file(std::move(pubkey_file)),
    privkey_file(std::move(privkey_file)),
    privkey_password(std::move(privkey_password))
{
    int portstart = server.find(':');
    if(portstart != -1) {
        port = server.substr(portstart + 1, server.size());
        server = server.substr(0, portstart);
    } else {
        port = "22";
    }

}

// ripped off: https://www.libssh2.org/examples/scp.html
char* SSHConnection::fetch_file() {
    std::call_once(sockets_initialized, &initializeSockets);
    std::call_once(libssh2_initialized, [](){libssh2_init(0);});

    // I have no idea what happens here
    libssh2_socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port.c_str()));
    addr.sin_addr.s_addr = inet_addr(server.c_str());

    if(connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        return nullptr;
    }

    LIBSSH2_SESSION* session = libssh2_session_init();

    if(!session) {
        return nullptr;
    }

    int handshake_failure = libssh2_session_handshake(session, sock);
    if(handshake_failure) {
       return nullptr;
    }

    const char* fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA256);
    // Check fingerprint here!

    if(auth_type == authentication_t::password) {
        if(libssh2_userauth_password(session, username.c_str(), password.c_str())) {
            return nullptr;
        }
    } else if(auth_type == authentication_t::pubkey) {
        if(libssh2_userauth_publickey_fromfile(session, username.c_str(), pubkey_file.c_str(), privkey_file.c_str(), privkey_password.c_str())) {
            return nullptr;
        }
    }

    libssh2_struct_stat fileinfo;
    LIBSSH2_CHANNEL* channel = libssh2_scp_recv2(session, path.c_str(), &fileinfo);

    if(!channel) {
        return nullptr;
    }

    char* memory = new char[fileinfo.st_size];
    int result = libssh2_channel_read(channel, memory, fileinfo.st_size);

    if(result < 0) {
        return nullptr;
    }


    libssh2_channel_free(channel);

    libssh2_session_disconnect(session, "Finished download, thank you for the files");
    libssh2_session_free(session);
    close_socket(sock);

    return memory;
}
