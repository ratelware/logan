#ifndef BOOKMARKSVIEW_H
#define BOOKMARKSVIEW_H

#include <QDockWidget>

namespace Ui {
class BookmarksView;
}

class BookmarksView : public QDockWidget
{
    Q_OBJECT

public:
    explicit BookmarksView(QWidget *parent = nullptr);
    ~BookmarksView();

private:
    Ui::BookmarksView *ui;
};

#endif // BOOKMARKSVIEW_H
