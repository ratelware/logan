#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <executor/license_item_t.h>

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();


public slots:
    void openItem(int index);

private:
    void setUpLicenses();

    Ui::AboutDialog *ui;
    std::vector<license_item_t> items;
};

#endif // ABOUTDIALOG_H
