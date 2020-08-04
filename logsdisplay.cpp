#include <QTextStream>
#include <QLayout>
#include <QPlainTextEdit>
#include <QTextOption>


#include "logsdisplay.h"
#include "singlelogdisplay.h"
#include "ui_logsdisplay.h"
#include "ui_singlelogdisplay.h"

LogsDisplay::LogsDisplay(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::LogsDisplay)
{
    ui->setupUi(this);
    setObjectName(QString("MultiLogDisplay"));
}

void LogsDisplay::displayFile(QFile& file) {
    QTextStream in(&file);
    QStringList text = in.readAll().split(QString("\n"));
    newTab(text, file.fileName());
}

void LogsDisplay::applyGrep(grep_structure g) {
    QStringList l;
    QString query = QString::fromStdString(g.search_query);
    if(!g.is_case_sensitive) {
        query = query.toUpper();
    }

    auto active = currentWidget();
    if(active == nullptr) {
        return;
    }

    if(active->objectName() == QString("SingleLogDisplay")) {
        if(currentIndex() == 0) {
            for(auto& t : dynamic_cast<SingleLogDisplay*>(active)->text) {
                QString cmp = (g.is_case_sensitive) ? t : t.toUpper();

                if(cmp.contains(query) ^ g.is_reverse) {
                    l.push_back(t);
                }
            }

            newTab(l, QString::fromStdString(g.search_query));
        } else {
            auto activeTab = currentIndex();
            mutateToNewTree()->applyGrep(g);
            setCurrentIndex(activeTab);
        }
    } else if(active->objectName() == QString("MultiLogDisplay")) {
        dynamic_cast<LogsDisplay*>(active)->applyGrep(g);
    }
}

void LogsDisplay::applySearch(search_structure s) {
    auto active = currentWidget();
    if(active == nullptr) {
        return;
    }

    if(active->objectName() == QString("SingleLogDisplay")) {
        dynamic_cast<SingleLogDisplay*>(active)->applySearch(s);
    } else if(active->objectName() == QString("MultiLogDisplay")) {
        dynamic_cast<LogsDisplay*>(active)->applySearch(s);
    }
}

void LogsDisplay::newTab(QStringList content, QString tabName) {
    if(parent() != nullptr && (count() == 0 || currentIndex() == 0)) {
        auto logDisplay = new SingleLogDisplay(content, this);
        auto newTab = addTab(logDisplay, QString(tabName));
        setCurrentIndex(newTab);
    } else {
        auto newDisplay = new LogsDisplay(this);

        newDisplay->newTab(content, QString("base"));
        auto newTab = addTab(newDisplay, tabName);
        setCurrentIndex(newTab);
    }
}

LogsDisplay* LogsDisplay::mutateToNewTree() {
    auto active = dynamic_cast<SingleLogDisplay*>(currentWidget());
    QStringList displayed = active->text;
    auto newDisplay = new LogsDisplay(this);

    newDisplay->newTab(displayed, QString("base"));
    auto current = currentIndex();
    auto currentTitle = tabText(current);
    removeTab(current);
    insertTab(current, newDisplay, currentTitle);
    return newDisplay;
}

LogsDisplay::~LogsDisplay()
{
    delete ui;
}
