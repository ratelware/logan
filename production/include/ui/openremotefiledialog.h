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
    explicit OpenRemoteFileDialog(std::shared_ptr<project_workspace>, QWidget *parent = nullptr);
    ~OpenRemoteFileDialog();

signals:
    void remoteFileSelected(QString downloadedPath);

public slots:
    void downloadAndOpenRemoteFile();

private:
    Ui::OpenRemoteFileDialog *ui;
    std::shared_ptr<project_workspace> workspace;
};

#endif // OPENREMOTEFILEDIALOG_H
