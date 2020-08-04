#include <qfile.h>
#include <qtextstream.h>
#include <qshortcut.h>
#include <memory>

#include <iostream>


#include "logan.h"
#include "grepwindow.h"
#include "ui_logan.h"

Logan::Logan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logan)
{
    ui->setupUi(this);

    auto file_handler = file_manager.open_file("I:/Ratelware/logan-2/logan2/example-empty-logfile");

    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_G), this)));
    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this)));
    connect(shortcuts[0].get(), &QShortcut::activated, this, &Logan::displayGrepWindow);
    connect(shortcuts[1].get(), &QShortcut::activated, this, &Logan::displaySearchWindow);

    connect(&g, &GrepWindow::greppingRequested, ui->display, &LogsDisplay::applyGrep);
    connect(&s, &SearchWindow::searchingRequested, ui->display, &LogsDisplay::applySearch);

    ui->display->displayFile(file_handler);
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

