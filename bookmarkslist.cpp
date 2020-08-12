#include "bookmarkslist.h"
#include "ui_bookmarkslist.h"
#include "bookmark.h"

BookmarksList::BookmarksList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookmarksList)
{
    ui->setupUi(this);
}

void BookmarksList::reload(doc_supervisor& s) {
    ui->bookmarksList->clear();
    const std::vector<bookmark_structure>& bs = s.get_bookmarks();

    for(auto b: bs) {
        ui->bookmarksList->addItem(new Bookmark(ui->bookmarksList, b));
    }
}

void BookmarksList::setRoot(RootLogfileDisplay* d) {
    root = d;
    connect(ui->bookmarksList, &QListWidget::itemClicked, root, &RootLogfileDisplay::scrollToLineOnCurrent);
}

BookmarksList::~BookmarksList()
{
    delete ui;
}
