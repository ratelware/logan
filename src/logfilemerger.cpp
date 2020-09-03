#include "logfilemerger.h"
#include "ui_logfilemerger.h"

LogfileMerger::LogfileMerger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogfileMerger)
{
    ui->setupUi(this);
}

LogfileMerger::~LogfileMerger()
{
    delete ui;
}
