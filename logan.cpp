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

    QTextStream in(&file);
    text = in.readAll().split(QString("\n"));
    ui->display->setContent(text.join(QString("\n")));

    connect(&g, &GrepWindow::greppingRequested, this, &Logan::applyGrep);
}

void Logan::displayGrepWindow() {
    g.cleanQuery();
    g.show();
}

void Logan::applyGrep(grep_structure g) {
    QStringList l;
    QString query = QString::fromStdString(g.search_query);
    if(!g.is_case_sensitive) {
        query = query.toUpper();
    }
    for(auto& t : text) {
        QString cmp = (g.is_case_sensitive) ? t : t.toUpper();

        if(cmp.contains(query) ^ g.is_reverse) {
            l.push_back(t);
        }
    }

    ui->display->setContent(l.join("\n"));
}

Logan::~Logan()
{
    delete ui;
}

