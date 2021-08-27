#include <executor/sshconnection.h>

#include <libssh2.h>
#include <libssh2_sftp.h>
#include <mutex>
#include <memory>

namespace {

std::once_flag sockets_initialized;
std::once_flag libssh2_initialized;

    bool initializeSockets(QMessageLogger& logger) {
    #ifdef WIN32
        WSADATA wsadata;
        int err;

        err = WSAStartup(MAKEWORD(2, 0), &wsadata);
        if(err != 0) {
            logger.critical("WSAStartup failed with error: %d\n", err);
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

    int detailed_error() {
#ifdef WIN32
        return WSAGetLastError();
#else
        return errno;
#endif

    }
}

ssh_credentials::ssh_credentials(QMessageLogger& logger): logger(logger)
{}

authentication_result ssh_credentials::interpret(int return_code) const {
    switch(return_code) {
    case 0:
        logger.debug("Auth successful");
        return authentication_result::passed;
    case LIBSSH2_ERROR_EAGAIN:
        logger.debug("Auth failed: try again later");
        return authentication_result::failed_tryagain;

    case LIBSSH2_ERROR_SOCKET_SEND:
    case LIBSSH2_ERROR_SOCKET_DISCONNECT:
    case LIBSSH2_ERROR_SOCKET_RECV:
    case LIBSSH2_ERROR_SOCKET_TIMEOUT:
    case LIBSSH2_ERROR_BAD_SOCKET:
    case LIBSSH2_ERROR_SOCKET_NONE:
        logger.debug("Auth failed: socket error %d", return_code);
        return authentication_result::failed_socket;

    case LIBSSH2_ERROR_PASSWORD_EXPIRED:
        logger.debug("Auth failed: password expired");
        return authentication_result::failed_password_expired;

    case LIBSSH2_ERROR_AUTHENTICATION_FAILED:
        logger.debug("Auth failed: cannot authenticate");
        return authentication_result::failed_auth_failure;

    default:
        logger.debug("Auth failed: generic error %d", return_code);
        return authentication_result::failed_generic;

    }

}

password_auth::password_auth(QMessageLogger& logger, std::string username, std::string password) :
    ssh_credentials(logger), username(username), password(password)
{}

authentication_result password_auth::authenticate(LIBSSH2_SESSION* session) const
{
    return interpret(libssh2_userauth_password(session, username.c_str(), password.c_str()));
}

pubkey_auth::pubkey_auth(QMessageLogger& logger, std::string username, std::string pubkey_file, std::string privkey_file, std::string privkey_password):
    ssh_credentials(logger), username(username), pubkey_file(pubkey_file), privkey_file(privkey_file), privkey_password(privkey_password)
{}

authentication_result pubkey_auth::authenticate(LIBSSH2_SESSION* session) const
{
    logger.debug("Using private key from file: %s", privkey_file.c_str());
    return interpret(libssh2_userauth_publickey_fromfile(session, username.c_str(), nullptr, privkey_file.c_str(), nullptr));
}

ssh_connection_token::ssh_connection_token(libssh2_socket_t so) : session(nullptr), socket(so)
{}

ssh_connection_token::~ssh_connection_token() {
    if(session != nullptr) {
        libssh2_session_disconnect(session, "Finished interaction, have a great day");
        libssh2_session_free(session);
    }

    close_socket(socket);
}

ssh_connection::ssh_connection(
    QMessageLogger& logger,
    std::string server,
    std::string path,
    const ssh_credentials& credentials
    ):
    logger(logger),
    server(server),
    path(path),
    credentials(credentials)

{
    int portstart = server.find(':');
    if(portstart != -1) {
        port = server.substr(portstart + 1, server.size());
        server = server.substr(0, portstart);
    } else {
        port = "22";
    }
}

std::vector<std::string> ssh_connection::list_dir(std::string path) const {
    std::optional<ssh_connection_token> opt_session = establish_connection();

    if(!opt_session.has_value()) {
        logger.info("Failed to establish connection. Dropping listing");
        return std::vector<std::string>();
    }

    ssh_connection_token session = opt_session.value();
    LIBSSH2_SFTP* sftp_session = libssh2_sftp_init(session.session);
    if(sftp_session == nullptr) {
        logger.info("Failed to establish SFTP session. Dropping listing");
        return std::vector<std::string>();
    }

    libssh2_session_set_blocking(session.session, 1);

    LIBSSH2_SFTP_HANDLE* handle = libssh2_sftp_opendir(sftp_session, path.c_str());
    if(handle == nullptr) {
        logger.info("Failed to establish SFTP handle. Dropping listing");
        return std::vector<std::string>();
    }


    std::vector<std::string> files;

    do {
        char mem[1024];
        char entry[1024];
        LIBSSH2_SFTP_ATTRIBUTES attrs;

        int result = libssh2_sftp_readdir_ex(handle, mem, sizeof(mem), entry, sizeof(entry), &attrs);
        if(result > 0) {
            if(entry[0] != '\0') {
                files.push_back(std::string(entry));
                logger.debug("%s", entry);
            }
        } else {
            break;
        }

    } while(true);

}

// ripped off: https://www.libssh2.org/examples/scp.html
char* ssh_connection::fetch_file() const {
    std::optional<ssh_connection_token> opt_session = establish_connection();

    if(!opt_session.has_value()) {
        logger.info("Failed to establish connection. Dropping file download");
        return nullptr;
    }

    ssh_connection_token session = opt_session.value();

    libssh2_struct_stat fileinfo;
    LIBSSH2_CHANNEL* channel = libssh2_scp_recv2(session.session, path.c_str(), &fileinfo);

    if(!channel) {
        logger.info("Failed to set up channel");
        return nullptr;
    }

    char* memory = new char[fileinfo.st_size];
    int read_error = libssh2_channel_read(channel, memory, fileinfo.st_size);

    if(read_error < 0) {
        logger.info("Got error reading response: %d", read_error);
        return nullptr;
    }


    libssh2_channel_free(channel);


    return memory;
}

std::optional<ssh_connection_token> ssh_connection::establish_connection() const {
    std::call_once(sockets_initialized, [this](){initializeSockets(logger);});
    std::call_once(libssh2_initialized, [](){libssh2_init(0);});

    // I have no idea what happens here
    ssh_connection_token conn(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));

    logger.debug("Connecting with to %s:%s", server.c_str(), port.c_str());

    sockaddr_in in_addr;
    in_addr.sin_family = AF_INET;
    in_addr.sin_port = htons(atoi(port.c_str()));
    in_addr.sin_addr.s_addr = inet_addr(server.c_str());

    logger.debug("Connecting with %d/%d to %ld:%d", in_addr.sin_family, in_addr.sin_family, in_addr.sin_addr.s_addr, in_addr.sin_port);


    auto connection_failure = connect(conn.socket, reinterpret_cast<sockaddr*>(&in_addr), sizeof(sockaddr_in));
    if(connection_failure) {
        logger.info("Failed to connect. Error: %d, %d", connection_failure, detailed_error());

        return std::nullopt;
    }

    conn.session = libssh2_session_init();

    if(!conn.session) {
        logger.info("Failed to create session");
        return std::nullopt;
    }

    int handshake_failure = libssh2_session_handshake(conn.session, conn.socket);
    if(handshake_failure) {
        logger.info("Failed handshake: %d", handshake_failure);
        return std::nullopt;
    }

    const char* fingerprint = libssh2_hostkey_hash(conn.session, LIBSSH2_HOSTKEY_HASH_SHA256);
    // Check fingerprint here!

    if(credentials.authenticate(conn.session) != authentication_result::passed) {
        return std::nullopt;
    }

    return std::move(conn);
}
