#ifndef LOGAN_H
#define LOGAN_H

#include <QMainWindow>
#include <QShortcut>
#include <QStringList>

#include "grep_structure.h"
#include "grepwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Logan; }
QT_END_NAMESPACE

class Logan : public QMainWindow
{
    Q_OBJECT

public:
    Logan(QWidget *parent = nullptr);
    ~Logan();

public slots:
    void displayGrepWindow();

private:
    Ui::Logan *ui;
    std::vector<std::unique_ptr<QShortcut>> shortcuts;
    GrepWindow g;
};
#endif // LOGAN_H
