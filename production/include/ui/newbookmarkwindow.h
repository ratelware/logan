#ifndef NEWBOOKMARKWINDOW_H
#define NEWBOOKMARKWINDOW_H

#include <QDialog>
#include <QIcon>

#include <executor/line_descriptor.h>
#include <executor/bookmark_structure.h>

namespace Ui {
class NewBookmarkWindow;
}

class RootLogfileDisplay;
class BookmarksList;

class NewBookmarkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewBookmarkWindow(line_number_t lineNum, QString defaultText, RootLogfileDisplay* target, QWidget *parent = nullptr);
    NewBookmarkWindow(bookmark_structure original, BookmarksList* bookmarks, QWidget *parent = nullptr);
    ~NewBookmarkWindow();


public slots:
    void showIconMenu();
    void setBookmarkIcon(QIcon icon);

    void addBookmark();
private:
    void initialize();

    Ui::NewBookmarkWindow *ui;

    line_number_t bookmarkLine;
    QString text;
    QIcon icon;
    RootLogfileDisplay* target;
    BookmarksList* bookmarks;
};

#endif // NEWBOOKMARKWINDOW_H
