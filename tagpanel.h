#ifndef TAGPANEL_H
#define TAGPANEL_H

#include <QScrollArea>

namespace Ui {
class TagPanel;
}

class TagPanel : public QScrollArea
{
    Q_OBJECT

public:
    explicit TagPanel(QWidget *parent = nullptr);
    ~TagPanel();

private:
    Ui::TagPanel *ui;
};

#endif // TAGPANEL_H
