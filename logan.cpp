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
    QFile file("I:/Ratelware/logan-2/logan2/example-empty-logfile");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_G), this)));
    connect(shortcuts[0].get(), &QShortcut::activated, this, &Logan::displayGrepWindow);

    this->ui->display->displayFile(file);
    connect(&g, &GrepWindow::greppingRequested, this->ui->display, &LogsDisplay::applyGrep);
}

void Logan::displayGrepWindow() {
    g.cleanQuery();
    g.show();
}


Logan::~Logan()
{
    delete ui;
}

