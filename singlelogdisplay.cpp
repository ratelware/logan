#include "singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

SingleLogDisplay::SingleLogDisplay(QStringList& l, QWidget *parent) :
    QWidget(parent),
    text(l),
    ui(new Ui::SingleLogDisplay)
{
    ui->setupUi(this);

    setObjectName(QString("SingleLogDisplay"));

    ui->display->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    ui->display->setWordWrapMode(QTextOption::NoWrap);
    ui->display->setReadOnly(true);
    ui->display->setOverwriteMode(false);

    ui->display->setPlainText(text.join(QString("\n")));
}

SingleLogDisplay::~SingleLogDisplay()
{
    delete ui;
}
