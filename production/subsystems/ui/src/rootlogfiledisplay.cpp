#include "ui/rootlogfiledisplay.h"
#include "ui_rootlogfiledisplay.h"

#include <QFileInfo>
#include <QDropEvent>
#include <QMimeData>

#include "ui/logsdisplay.h"
#include "ui/bookmark.h"

RootLogfileDisplay::RootLogfileDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootLogfileDisplay)
{
    ui->setupUi(this);
    ui->bookmarksList->setRoot(this);
    connect(ui->tabs, &QTabWidget::currentChanged, this, &RootLogfileDisplay::tabChanged);
    connect(ui->tabs, &QTabWidget::tabCloseRequested, this, &RootLogfileDisplay::handleTabClosing);
    connect(ui->bookmarks, &QWidget::customContextMenuRequested, ui->bookmarksList, &BookmarksList::showContextMenu);
}

void RootLogfileDisplay::handleTabClosing(int tabId) {
    if(tabId < ui->tabs->count()) {
        ui->tabs->removeTab(tabId);
        manager.remove_supervisor(tabId);
    }
}

void RootLogfileDisplay::tabChanged(int newTab) {
    if(newTab >= 0 && newTab < ui->tabs->count()) {
        auto& active_supervisor = manager.supervisor_at(newTab);
        ui->bookmarksList->reload(active_supervisor);
    }
}

void RootLogfileDisplay::scrollToLineOnCurrent(QListWidgetItem* bkmark) {
    Bookmark* bookmark = dynamic_cast<Bookmark*>(bkmark);
    auto line = bookmark->getLine();


    dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget())->scrollToLine(line);
}

void RootLogfileDisplay::applyGrepToCurrent(filter* g) {
    auto logs = dynamic_cast<LogsDisplay*>(ui->tabs->currentWidget());
    if(logs != nullptr) {
        logs->applyGrep(std::unique_ptr<filter>(g));
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

void RootLogfileDisplay::dropEvent(QDropEvent *event) {
    const QMimeData* mime = event->mimeData();
    if(mime->hasUrls()) {
        for (int i = 0; i < mime->urls().size(); ++i)
        {
            fileSelected(mime->urls().at(i).toLocalFile());
        }
    }
}

void RootLogfileDisplay::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData* mime = event->mimeData();
    if(mime->hasUrls()) {
        event->accept();
    }
}

RootLogfileDisplay::~RootLogfileDisplay()
{
    delete ui;
}
