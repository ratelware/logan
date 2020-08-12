#ifndef BOOKMARKSVIEW_H
#define BOOKMARKSVIEW_H

#include <QDockWidget>

#include "doc_supervisor.h"

namespace Ui {
class BookmarksView;
}

class BookmarksView : public QDockWidget
{
    Q_OBJECT

public:
    explicit BookmarksView(QWidget *parent = nullptr);
    ~BookmarksView();

    void reload(doc_supervisor&);
private:
    Ui::BookmarksView *ui;
};

#endif // BOOKMARKSVIEW_H
