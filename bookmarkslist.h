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
private:
    RootLogfileDisplay* root;
    Ui::BookmarksList *ui;
};

#endif // BOOKMARKSLIST_H
