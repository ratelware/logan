#include "ui/bookmarkslist.h"
#include "ui_bookmarkslist.h"
#include <ui/bookmark.h>
#include "ui/newbookmarkwindow.h"

#include <QAction>
#include <QGuiApplication>
#include <QClipboard>
#include <QMenu>
#include <QInputDialog>
#include <QKeyEvent>

BookmarksList::BookmarksList(QWidget *parent) :
    QWidget(parent),
    supervisor(nullptr),
    ui(new Ui::BookmarksList)
{
    ui->setupUi(this);
}

void BookmarksList::reload(doc_supervisor& s)
{
    ui->bookmarksList->clear();
    supervisor = &s;
    const std::vector<bookmark_t>& bs = supervisor->get_bookmarks();

    ui->bookmarksList->setIconSize(QSize(24, 24));

    for(const auto& b: bs) {
        ui->bookmarksList->addItem(new Bookmark(ui->bookmarksList, b));
    }
}

void BookmarksList::keyReleaseEvent(QKeyEvent* ev) {
    if(ev->key() == Qt::Key_Delete) {
        auto activeRow = ui->bookmarksList->currentRow();
        if(activeRow >= 0) {
            deleteActive();
        }

        auto remainingRows = ui->bookmarksList->count();
        if(remainingRows > 0) {
            ui->bookmarksList->setCurrentRow(activeRow > remainingRows - 1 ? remainingRows - 1 : activeRow);
            ui->bookmarksList->item(activeRow > remainingRows - 1 ? remainingRows - 1 : activeRow)->setSelected(true);
        }
    }
}

void BookmarksList::copyActive() {
    auto items = ui->bookmarksList->selectedItems();
    auto text = QStringList();
    for(auto i: items) {
        text.append(dynamic_cast<Bookmark*>(i)->structure().bookmark_name);
    }

    QGuiApplication::clipboard()->setText(text.join("\n"));
}

void BookmarksList::editActive() {
    for(auto i: ui->bookmarksList->selectedItems()) {
        auto bookmark = dynamic_cast<Bookmark*>(i);
        NewBookmarkWindow b(bookmark->structure(), this);
        b.exec();
    }
}

void BookmarksList::updateBookmark(bookmark_t b) {
    supervisor->update_bookmark(b.line_number, b);
    reload(*supervisor);
}

void BookmarksList::deleteActive() {
    auto items = ui->bookmarksList->selectedItems();

    std::vector<line_number_t> bookmarks;
    for(auto i: items) {
        bookmarks.push_back(dynamic_cast<Bookmark*>(i)->getLine());
        ui->bookmarksList->removeItemWidget(i);
    }

    supervisor->remove_bookmarks(bookmarks);
    reload(*supervisor);
}

void BookmarksList::setRoot(RootLogfileDisplay* d) {
    root = d;
    connect(ui->bookmarksList, &QListWidget::itemClicked, root, &RootLogfileDisplay::scrollToLineOnCurrent);
}

void BookmarksList::showContextMenu(const QPoint& pos) {
    auto copyAction = new QAction("Copy");
    auto editAction = new QAction("Edit bookmark");
    auto deleteAction = new QAction("Delete");

    auto all = QList<QAction*>({copyAction, editAction, deleteAction});

    if(ui->bookmarksList->selectedItems().isEmpty()) {
        editAction->setDisabled(true);
        copyAction->setDisabled(true);
        deleteAction->setDisabled(true);
    }

    connect(copyAction, &QAction::triggered, this, &BookmarksList::copyActive);
    connect(editAction, &QAction::triggered, this, &BookmarksList::editActive);
    connect(deleteAction, &QAction::triggered, this, &BookmarksList::deleteActive);

    QMenu menu;
    menu.addActions(all);
    menu.exec(parentWidget()->mapToGlobal(pos));
}

BookmarksList::~BookmarksList()
{
    delete ui;
}
