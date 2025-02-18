#include "ui/logfilemerger.h"
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

void LogfileMerger::dropEvent(QDropEvent *event) {

}

void LogfileMerger::dragEnterEvent(QDragEnterEvent *event) {

}


void LogfileMerger::addActiveOptionToActiveTab() {

}

void LogfileMerger::removeActiveOptionFromActiveTab() {

}

void LogfileMerger::addActiveFromAllToOptions() {

}

void LogfileMerger::removeActiveFromOptions() {

}

void LogfileMerger::moveFileUpInTab() {

}

void LogfileMerger::moveFileDownInTab() {


}

void LogfileMerger::addNewTab() {


}
