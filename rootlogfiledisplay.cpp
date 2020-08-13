#include "rootlogfiledisplay.h"
#include "ui_rootlogfiledisplay.h"

#include <QFileInfo>

#include "logsdisplay.h"
#include "bookmark.h"

RootLogfileDisplay::RootLogfileDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootLogfileDisplay)
{
    ui->setupUi(this);
    ui->bookmarksList->setRoot(this);
    connect(ui->tabs, &QTabWidget::currentChanged, this, &RootLogfileDisplay::tabChanged);
}

void RootLogfileDisplay::tabChanged(int newTab) {
    auto& active_supervisor = manager.supervisor_at(newTab);
    ui->bookmarksList->reload(active_supervisor);
}

void RootLogfileDisplay::scrollToLineOnCurrent(QListWidgetItem* bkmark) {
    qDebug("Started scrolling");
    Bookmark* bookmark = dynamic_cast<Bookmark*>(bkmark);
    auto line = bookmark->getLine();


    dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget())->scrollToLine(line);
}

void RootLogfileDisplay::applyGrepToCurrent(grep_structure g) {
    auto logs = dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget());
    if(logs != nullptr) {
        logs->applyGrep(g);
    }
}

void RootLogfileDisplay::applySearchToCurrent(search_structure g) {
    auto logs = dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget());
    if(logs != nullptr) {
        logs->applySearch(g);
    }
}

void RootLogfileDisplay::fileSelected(const QString& fileName) {
    auto& file_handler = manager.open_file(fileName);
    auto handler = file_handler.get_root().as(QString("<base>"));
    auto newLogs = new LogsDisplay(handler, this, *this);
    newLogs->newTab(handler);
    auto newOne = ui->tabs->addTab(newLogs, QFileInfo(fileName).fileName());
    ui->tabs->setCurrentIndex(newOne);
}

void RootLogfileDisplay::addBookmarkToCurrent(bookmark_structure b) {
    auto& active_supervisor = manager.supervisor_at(ui->tabs->currentIndex());
    active_supervisor.add_bookmark(b);
    ui->bookmarksList->reload(active_supervisor);
}

RootLogfileDisplay::~RootLogfileDisplay()
{
    delete ui;
}
