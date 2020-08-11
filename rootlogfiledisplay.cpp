#include "rootlogfiledisplay.h"
#include "ui_rootlogfiledisplay.h"

#include <QFileInfo>

#include "logsdisplay.h"

RootLogfileDisplay::RootLogfileDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootLogfileDisplay)
{
    ui->setupUi(this);
    connect(ui->tabs, &QTabWidget::currentChanged, this, &RootLogfileDisplay::tabChanged);
}

void RootLogfileDisplay::tabChanged(int newTab) {

}

void RootLogfileDisplay::applyGrepToCurrent(grep_structure g) {
    dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget())->applyGrep(g);
}

void RootLogfileDisplay::applySearchToCurrent(search_structure g) {
    dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget())->applySearch(g);
}

void RootLogfileDisplay::fileSelected(const QString& fileName) {
    auto& file_handler = manager.open_file(fileName);
    auto handler = file_handler.get_root().as(QString("<base>"));
    auto newLogs = new LogsDisplay(handler, this);
    newLogs->newTab(handler);
    ui->tabs->addTab(newLogs, QFileInfo(fileName).fileName());
}

RootLogfileDisplay::~RootLogfileDisplay()
{
    delete ui;
}
