#ifndef SSHCONNECTION_H
#define SSHCONNECTION_H

#include <string>

enum authentication_t {
    password,
    pubkey
};

class SSHConnection
{
public:
    SSHConnection(
        std::string server,
        std::string path,
        std::string username,

        authentication_t auth_type,
        std::string password,

        std::string pubkey_file,
        std::string privkey_file,
        std::string privkey_password
    );

    char* fetch_file();

private:
    std::string server;
    std::string path;
    std::string username;
    std::string port;

    authentication_t auth_type;
    std::string password;

    std::string pubkey_file;
    std::string privkey_file;
    std::string privkey_password;
};

#endif // SSHCONNECTION_H
