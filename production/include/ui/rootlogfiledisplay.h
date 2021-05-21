#ifndef ROOTLOGFILEDISPLAY_H
#define ROOTLOGFILEDISPLAY_H

#include <QWidget>
#include <QListWidgetItem>

#include "logfile_manager.h"
#include "line_descriptor.h"
#include "search_structure.h"

namespace Ui {
class RootLogfileDisplay;
}

class RootLogfileDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit RootLogfileDisplay(QWidget *parent = nullptr);
    ~RootLogfileDisplay();

    void addBookmarkToCurrent(bookmark_structure b);

public slots:
    void tabChanged(int newActive);
    void fileSelected(const QString& filename);
    void scrollToLineOnCurrent(QListWidgetItem* bookmarkItem);
    void scrollToLineOnCurrent(line_number_t line);

    void applyGrepToCurrent(filter* g);
    void applySearchToCurrent(search_structure s);
    void handleTabClosing(int tabId);

    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

private:
    logfile_manager manager;
    Ui::RootLogfileDisplay *ui;
};

#endif // ROOTLOGFILEDISPLAY_H
