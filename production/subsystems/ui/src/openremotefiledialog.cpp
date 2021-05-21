#include "ui/openremotefiledialog.h"
#include "ui_openremotefiledialog.h"

OpenRemoteFileDialog::OpenRemoteFileDialog(project_controller& pc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenRemoteFileDialog),
    controller(pc)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &OpenRemoteFileDialog::downloadAndOpenRemoteFile);
}

void OpenRemoteFileDialog::downloadAndOpenRemoteFile() {

}

OpenRemoteFileDialog::~OpenRemoteFileDialog()
{
    delete ui;
}
