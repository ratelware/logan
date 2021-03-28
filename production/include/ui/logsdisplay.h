#ifndef LOGSDISPLAY_H
#define LOGSDISPLAY_H

#include <QTabWidget>
#include <QFile>

#include "grep_structure.h"
#include "search_structure.h"
#include "line_descriptor.h"
#include "logfile_handler.h"
#include "rootlogfiledisplay.h"

namespace Ui {
class LogsDisplay;
}

class LogsDisplay : public QTabWidget
{
    Q_OBJECT

public:
    explicit LogsDisplay(logfile_proxy handler, QWidget *parent, RootLogfileDisplay& root);
    ~LogsDisplay();

    void newTab(logfile_proxy logfile);
    LogsDisplay* mutateToNewTree();

public:
    void applyGrep(std::unique_ptr<filter>&& g);
    void applySearch(search_structure g);

    void scrollToLine(line_number_t line);
    void handleTabClosing(int tabId);

private:
    Ui::LogsDisplay *ui;
    QVector<LogsDisplay> children;
    logfile_proxy log_handler;
    RootLogfileDisplay& root;
};

#endif // LOGSDISPLAY_H
