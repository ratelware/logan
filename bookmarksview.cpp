#include "bookmarksview.h"
#include "ui_bookmarksview.h"

#include "bookmark.h"

#include <QStringListModel>

BookmarksView::BookmarksView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::BookmarksView)
{
    ui->setupUi(this);
    ui->bookmarkList->raise();
}

void BookmarksView::reload(doc_supervisor& s) {
    ui->bookmarkList->clear();
    const std::vector<bookmark_structure>& bs = s.get_bookmarks();

    for(auto b: bs) {
        ui->bookmarkList->addItem(b.bookmark_name);
    }
}

BookmarksView::~BookmarksView()
{
    delete ui;
}
