#include "ui/aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDir>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    setUpLicenses();

    connect(this->ui->selectBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AboutDialog::openItem);
    openItem(0);
    setWindowIcon(QIcon(":icons/racoon.png"));
}

void AboutDialog::openItem(int index) {
    if(index < 0 || index >= items.size()) {
        return;
    }

    ui->about->setText(items[index].about);
    ui->licenseText->setPlainText(items[index].license_text);
}

void AboutDialog::setUpLicenses() {
    QFile licenseList(":/libraries/list.csv");
    if(!licenseList.open(QFile::ReadOnly)) {
        return;
    }

    QString all(QString(licenseList.readAll()));
    licenseList.close();
    QStringList licenses(all.split("\n"));

    for(QString l: licenses) {
        license_item_t lic;
        QStringList desc = l.split(",");
        if(desc.length() < 2) continue;

        lic.name = desc[0];
        QFile about(QString(":/libraries/") + desc[1].trimmed() + "/ABOUT.txt");
        if(!about.open(QFile::ReadOnly)) {
            continue;
        }
        lic.about = QString(about.readAll());
        about.close();


        QFile license(QString(":/libraries/") + desc[1].trimmed() + "/LICENSE.txt");
        if(!license.open(QFile::ReadOnly)) {
            continue;
        }
        lic.license_text = QString(license.readAll());
        license.close();

        items.push_back(lic);
        ui->selectBox->addItem(lic.name);
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
