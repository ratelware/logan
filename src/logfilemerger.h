#ifndef LOGFILEMERGER_H
#define LOGFILEMERGER_H

#include <QDialog>

namespace Ui {
class LogfileMerger;
}

class LogfileMerger : public QDialog
{
    Q_OBJECT

public:
    explicit LogfileMerger(QWidget *parent = nullptr);
    ~LogfileMerger();

    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);


public slots:
    void addActiveOptionToActiveTab();
    void removeActiveOptionFromActiveTab();
    void addActiveFromAllToOptions();
    void removeActiveFromOptions();
    void moveFileUpInTab();
    void moveFileDownInTab();
    void addNewTab();

private:
    Ui::LogfileMerger *ui;
};

#endif // LOGFILEMERGER_H
