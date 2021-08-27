#include "ui/openremotefiledialog.h"
#include "ui_openremotefiledialog.h"

#include <executor/sshconnection.h>

OpenRemoteFileDialog::OpenRemoteFileDialog(std::shared_ptr<project_workspace> pw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenRemoteFileDialog),
    workspace(pw)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &OpenRemoteFileDialog::downloadAndOpenRemoteFile);
}

void OpenRemoteFileDialog::downloadAndOpenRemoteFile() {
    auto logger = QMessageLogger();
    auto auth = pubkey_auth(logger, "root", "C:/Users/Ja/.ssh/id_putty.pub", "C:/Users/Ja/.ssh/id_rsa", "");

    ssh_connection c(
              logger,
              "88.99.14.12",
              "/var/log/syslog",
              auth
              );

  c.fetch_file();
  //c.list_dir("/var/log");
}

OpenRemoteFileDialog::~OpenRemoteFileDialog()
{
    delete ui;
}
