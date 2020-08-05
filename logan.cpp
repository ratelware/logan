#include <qfile.h>
#include <qtextstream.h>
#include <qshortcut.h>
#include <memory>

#include <iostream>


#include "logan.h"
#include "logsdisplay.h"
#include "grepwindow.h"
#include "ui_logan.h"

Logan::Logan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logan)
{
    ui->setupUi(this);

    auto& file_handler = file_manager.open_file("I:/Ratelware/logan-2/logan2/example-empty-logfile");
    auto handler = file_handler.as(QString("example-empty-logfile"));
    auto newLogs = new LogsDisplay(handler, this);
    newLogs->setObjectName("RootLogDisplay");
    ui->displayLayout->addWidget(newLogs);

    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_G), this)));
    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this)));
    connect(shortcuts[0].get(), &QShortcut::activated, this, &Logan::displayGrepWindow);
    connect(shortcuts[1].get(), &QShortcut::activated, this, &Logan::displaySearchWindow);

    connect(&g, &GrepWindow::greppingRequested, this, &Logan::applyGrep);
    connect(&s, &SearchWindow::searchingRequested, this, &Logan::applySearch);

    newLogs->newTab(handler);
}

void Logan::applyGrep(grep_structure g) {
    this->findChild<LogsDisplay*>("RootLogDisplay")->applyGrep(g);
}

void Logan::applySearch(search_structure g) {
    this->findChild<LogsDisplay*>("RootLogDisplay")->applySearch(g);
}

void Logan::displayGrepWindow() {
    if(!g.hasFocus()) {
        g.cleanQuery();
        g.show();
    }
}

void Logan::displaySearchWindow() {
    if(!s.isVisible()) {
        s.cleanQuery();
        s.show();
    }

    if(!s.hasFocus()) {
        s.activateWindow();
    }
}

void Logan::addBookmark(int lineNumber) {

}

Logan::~Logan()
{
    delete ui;
}

