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

private:
    Ui::LogfileMerger *ui;
};

#endif // LOGFILEMERGER_H
