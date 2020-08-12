#include "bookmarkslist.h"
#include "ui_bookmarkslist.h"

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
        ui->bookmarksList->addItem(b.bookmark_name);
    }
}

BookmarksList::~BookmarksList()
{
    delete ui;
}
