#ifndef LOGSDISPLAY_H
#define LOGSDISPLAY_H

#include <QTabWidget>
#include <QFile>

#include "grep_structure.h"
#include "search_structure.h"
#include "logfile_handler.h"

namespace Ui {
class LogsDisplay;
}

class LogsDisplay : public QTabWidget
{
    Q_OBJECT

public:
    explicit LogsDisplay(logfile_proxy handler, QWidget *parent = nullptr);
    ~LogsDisplay();

    void newTab(logfile_proxy logfile);
    LogsDisplay* mutateToNewTree();

public:
    void applyGrep(grep_structure g);
    void applySearch(search_structure g);

private:
    Ui::LogsDisplay *ui;
    QVector<LogsDisplay> children;
    logfile_proxy log_handler;
};

#endif // LOGSDISPLAY_H
