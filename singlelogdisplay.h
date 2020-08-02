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

public:
    Ui::SingleLogDisplay *ui;

public slots:
    void copySelectionToClipboard();

private:
    void setUpActions();
};

#endif // SINGLELOGDISPLAY_H
