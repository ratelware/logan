#ifndef GREPWINDOW_H
#define GREPWINDOW_H

#include <QDialog>

#include "grep_structure.h"

namespace Ui {
class GrepWindow;
}

class GrepWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GrepWindow(QWidget *parent = nullptr);
    ~GrepWindow();

    void cleanQuery();
    void setQuery(QString query);

public slots:
    void formGrep();

signals:
    void greppingRequested(grep_structure g);

private:
    Ui::GrepWindow *ui;
};

#endif // GREPWINDOW_H
