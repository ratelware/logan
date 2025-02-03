#ifndef BOOKMARKSLIST_H
#define BOOKMARKSLIST_H

#include <QWidget>

#include <executor/doc_supervisor.h>
#include <ui/rootlogfiledisplay.h>

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

    void updateBookmark(bookmark_t b);

public slots:
    void copyActive();
    void deleteActive();
    void editActive();

    void showContextMenu(const QPoint&);

    void keyReleaseEvent(QKeyEvent*);

private:
    RootLogfileDisplay* root{};
    doc_supervisor* supervisor;
    Ui::BookmarksList *ui;
};

#endif // BOOKMARKSLIST_H
