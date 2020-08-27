#ifndef BOOKMARKSLIST_H
#define BOOKMARKSLIST_H

#include <QWidget>

#include "doc_supervisor.h"
#include "rootlogfiledisplay.h"

namespace Ui {
class BookmarksList;
}

class BookmarksList : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarksList(QWidget *parent = nullptr);
    ~BookmarksList();

    void reload(doc_supervisor&);

    void setRoot(RootLogfileDisplay*);

    void updateBookmark(bookmark_structure b);

public slots:
    void copyActive();
    void deleteActive();
    void editActive();

    void showContextMenu(const QPoint&);

    void keyReleaseEvent(QKeyEvent*);

private:
    RootLogfileDisplay* root;
    doc_supervisor* supervisor;
    Ui::BookmarksList *ui;
};

#endif // BOOKMARKSLIST_H
