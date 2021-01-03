#include "openremotefiledialog.h"
#include "ui_openremotefiledialog.h"

OpenRemoteFileDialog::OpenRemoteFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenRemoteFileDialog)
{
    ui->setupUi(this);
}

OpenRemoteFileDialog::~OpenRemoteFileDialog()
{
    delete ui;
}
