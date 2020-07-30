#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>

namespace Ui {
class TagList;
}

class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(QWidget *parent = nullptr);
    ~TagList();

private:
    Ui::TagList *ui;
};

#endif // TAGLIST_H
