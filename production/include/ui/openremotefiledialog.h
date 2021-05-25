#ifndef OPENREMOTEFILEDIALOG_H
#define OPENREMOTEFILEDIALOG_H

#include <QDialog>

#include <executor/project_controller.h>

namespace Ui {
class OpenRemoteFileDialog;
}

class OpenRemoteFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenRemoteFileDialog(project_controller&, QWidget *parent = nullptr);
    ~OpenRemoteFileDialog();

public slots:
    void downloadAndOpenRemoteFile();

private:
    Ui::OpenRemoteFileDialog *ui;
    project_controller& controller;
};

#endif // OPENREMOTEFILEDIALOG_H
