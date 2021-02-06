#ifndef OPENREMOTEFILEDIALOG_H
#define OPENREMOTEFILEDIALOG_H

#include <QDialog>

namespace Ui {
class OpenRemoteFileDialog;
}

class OpenRemoteFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenRemoteFileDialog(QWidget *parent = nullptr);
    ~OpenRemoteFileDialog();

private:
    Ui::OpenRemoteFileDialog *ui;
};

#endif // OPENREMOTEFILEDIALOG_H
