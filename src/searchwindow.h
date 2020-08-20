#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QDialog>

#include "search_structure.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

    void cleanQuery();
    void setQuery(QString query);

public slots:
    void formSearch();


signals:
    void searchingRequested(search_structure s);

private:
    Ui::SearchWindow *ui;
};

#endif // FINDWINDOW_H
