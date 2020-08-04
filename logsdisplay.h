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
    explicit LogsDisplay(QWidget *parent = nullptr);
    ~LogsDisplay();

    void displayFile(logfile_handler& file);
    void newTab(QStringList content, QString tabName);
    LogsDisplay* mutateToNewTree();

public slots:
    void applyGrep(grep_structure g);
    void applySearch(search_structure g);

private:
    Ui::LogsDisplay *ui;
    QVector<LogsDisplay> children;
};

#endif // LOGSDISPLAY_H
