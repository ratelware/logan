#include "logsdisplay.h"
#include "ui_logsdisplay.h"

LogsDisplay::LogsDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogsDisplay)
{
    ui->setupUi(this);
}

LogsDisplay::~LogsDisplay()
{
    delete ui;
}

void LogsDisplay::setContent(QString s) {
    ui->logDisplay->setPlainText(s);
}
