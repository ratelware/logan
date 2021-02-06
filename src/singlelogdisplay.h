#ifndef SINGLELOGDISPLAY_H
#define SINGLELOGDISPLAY_H

#include <QWidget>
#include <QTextBlockFormat>

#include "search_structure.h"
#include "logfile_handler.h"

class LogsDisplay;
class RootLogfileDisplay;

namespace Ui {
class SingleLogDisplay;
}

class SingleLogDisplay : public QWidget
{
    Q_OBJECT

public:
    logfile_proxy logfile;

    explicit SingleLogDisplay(logfile_proxy l, LogsDisplay *parent, RootLogfileDisplay& root);
    ~SingleLogDisplay();

    void scrollToLine(line_number_t line);

public:
    Ui::SingleLogDisplay *ui;

public slots:
    void copySelectionToClipboard();
    void emphasiseSelection();
    void applySearch(search_structure s);
    void bookmark();
    void fastBookmark();

    void mousePressEvent(QMouseEvent *event);
private:
    void setUpActions();

    QList<QTextBlockFormat> existingFormats;
    RootLogfileDisplay& root;
};

#endif // SINGLELOGDISPLAY_H
