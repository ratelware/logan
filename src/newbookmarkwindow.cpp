#include "newbookmarkwindow.h"
#include "ui_newbookmarkwindow.h"

#include "bookmark_structure.h"
#include "iconmenupopup.h"
#include "configuration_manager.h"
#include "bookmarkslist.h"
#include "rootlogfiledisplay.h"

NewBookmarkWindow::NewBookmarkWindow(line_number_t lineNum, QString defaultText, RootLogfileDisplay* target, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBookmarkWindow),
    bookmarkLine(lineNum),
    text(defaultText),
    icon(QPixmap(configuration_manager::get_instance().icon_for_text(defaultText))),
    target(target),
    bookmarks(nullptr)
{
    initialize();
}

NewBookmarkWindow::NewBookmarkWindow(bookmark_structure original, BookmarksList* bookmarks, QWidget *parent):
    QDialog(parent),
    ui(new Ui::NewBookmarkWindow),
    bookmarkLine(original.line_number),
    text(original.bookmark_name),
    icon(original.icon),
    target(nullptr),
    bookmarks(bookmarks)
{
    initialize();
}

void NewBookmarkWindow::initialize() {
    setWindowIcon(QIcon(QPixmap(":/icons/bookmark.png")));

    ui->setupUi(this);
    ui->bookmarkName->setText(text);
    ui->bookmarkIcon->setIcon(icon);
    connect(ui->bookmarkIcon, &QPushButton::clicked, this, &NewBookmarkWindow::showIconMenu);
    connect(ui->approve, &QPushButton::clicked, this, &NewBookmarkWindow::addBookmark);
}

void NewBookmarkWindow::showIconMenu() {
    IconMenuPopup::getIcon(this);
}

void NewBookmarkWindow::setBookmarkIcon(QIcon i) {
    ui->bookmarkIcon->setIcon(i);
}

void NewBookmarkWindow::addBookmark() {
    bookmark_structure b;

    b.line_number = bookmarkLine;
    b.bookmark_name = ui->bookmarkName->text();
    b.icon = ui->bookmarkIcon->icon();

    if(target != nullptr) {
        target->addBookmarkToCurrent(b);
    } else if(bookmarks != nullptr) {
        bookmarks->updateBookmark(b);
    }
    close();
}

NewBookmarkWindow::~NewBookmarkWindow()
{
    delete ui;
}
