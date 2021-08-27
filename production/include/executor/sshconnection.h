#ifndef SSHCONNECTION_H
#define SSHCONNECTION_H

#include <libssh2.h>
#include <string>
#include <QMessageLogger>

enum authentication_result {
    passed,
    failed_generic,
    failed_socket,
    failed_password_expired,
    failed_auth_failure,
    failed_tryagain
};

class ssh_credentials {
public:
    ssh_credentials(QMessageLogger& logger);
    virtual authentication_result authenticate(LIBSSH2_SESSION* session) const = 0;

protected:
    QMessageLogger& logger;

    authentication_result interpret(int return_code) const;
};

class password_auth : public ssh_credentials {
public:
  password_auth(
          QMessageLogger& logger,
          std::string username,
          std::string password
          );

public:
  virtual authentication_result authenticate(LIBSSH2_SESSION* session) const;

private:
  std::string username;
  std::string password;
};

class pubkey_auth : public ssh_credentials {
public:
    pubkey_auth(
            QMessageLogger& logger,
            std::string username,
            std::string pubkey_file,
            std::string privkey_file,
            std::string privkey_password);

public:
    virtual authentication_result authenticate(LIBSSH2_SESSION* session) const;

private:
    std::string username;
    std::string pubkey_file;
    std::string privkey_file;
    std::string privkey_password;
};

class ssh_connection_token {
public:
    ssh_connection_token(libssh2_socket_t so);
    ~ssh_connection_token();

    LIBSSH2_SESSION* session;
    libssh2_socket_t socket;
};

class ssh_connection
{
public:
    ssh_connection(
        QMessageLogger& logger,
        std::string server,
        std::string path,
        const ssh_credentials& credentials
    );

    char* fetch_file() const;
    std::vector<std::string> list_dir(std::string path) const;

private:
    QMessageLogger& logger;
    std::string server;
    std::string path;
    std::string port;

    const ssh_credentials& credentials;

    std::optional<ssh_connection_token> establish_connection() const;
};

#endif // SSHCONNECTION_H
