#include "bookmarksview.h"
#include "ui_bookmarksview.h"

BookmarksView::BookmarksView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::BookmarksView)
{
    ui->setupUi(this);
}

BookmarksView::~BookmarksView()
{
    delete ui;
}
