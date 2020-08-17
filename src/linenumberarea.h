#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>

namespace Ui {
class LineNumberArea;
}

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    explicit LineNumberArea(QWidget *parent = nullptr);
    ~LineNumberArea();

    QSize sizeHint() const override {
        return QSize(30, 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {

    }


private:
    Ui::LineNumberArea *ui;
};

#endif // LINENUMBERAREA_H
