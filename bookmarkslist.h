#ifndef BOOKMARKSLIST_H
#define BOOKMARKSLIST_H

#include <QWidget>

#include "doc_supervisor.h"

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
private:
    Ui::BookmarksList *ui;
};

#endif // BOOKMARKSLIST_H
