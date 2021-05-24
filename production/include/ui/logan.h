#ifndef LOGAN_H
#define LOGAN_H

#include <QMainWindow>
#include <QShortcut>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QListWidgetItem>

#include "grep_structure.h"
#include "grepwindow.h"
#include "searchwindow.h"
#include "logfile_manager.h"
#include "project_controller.h"

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
    void displaySearchWindow();
    void displayAboutWindow();
    void openNewLocalFile();
    void openNewRemoteFile();
    void createNewProjectAction();
    void openExistingProjectAction();
    void setActiveProjectLocation(QString location);

private:
    QString getSelectedText() const;

    Ui::Logan *ui;
    std::vector<std::unique_ptr<QShortcut>> shortcuts;
    GrepWindow g;
    SearchWindow s;
    project_controller project_controller;
};
#endif // LOGAN_H
