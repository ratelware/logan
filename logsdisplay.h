#ifndef LOGSDISPLAY_H
#define LOGSDISPLAY_H

#include <QWidget>

namespace Ui {
class LogsDisplay;
}

class LogsDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit LogsDisplay(QWidget *parent = nullptr);
    ~LogsDisplay();

    void setContent(QString s);

private:
    Ui::LogsDisplay *ui;
};

#endif // LOGSDISPLAY_H
