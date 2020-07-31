#ifndef LOGSDISPLAY_H
#define LOGSDISPLAY_H

#include <QTabWidget>
#include <QFile>

#include "grep_structure.h"

namespace Ui {
class LogsDisplay;
}

class LogsDisplay : public QTabWidget
{
    Q_OBJECT

public:
    explicit LogsDisplay(QWidget *parent = nullptr);
    ~LogsDisplay();

    void displayFile(QFile& file);
    void newTab(QStringList content, QString tabName);
    LogsDisplay* mutateToNewTree();

public slots:
    void applyGrep(grep_structure g);

private:
    Ui::LogsDisplay *ui;
    QVector<LogsDisplay> children;
};

#endif // LOGSDISPLAY_H
