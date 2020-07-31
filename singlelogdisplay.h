#ifndef SINGLELOGDISPLAY_H
#define SINGLELOGDISPLAY_H

#include <QWidget>

namespace Ui {
class SingleLogDisplay;
}

class SingleLogDisplay : public QWidget
{
    Q_OBJECT

public:
    QStringList text;

    explicit SingleLogDisplay(QStringList& l, QWidget *parent = nullptr);
    ~SingleLogDisplay();

private:
    Ui::SingleLogDisplay *ui;
};

#endif // SINGLELOGDISPLAY_H
