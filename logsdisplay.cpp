#include <QTextStream>
#include <QLayout>
#include <QPlainTextEdit>
#include <QTextOption>


#include "logsdisplay.h"
#include "singlelogdisplay.h"
#include "ui_logsdisplay.h"
#include "ui_singlelogdisplay.h"

LogsDisplay::LogsDisplay(logfile_proxy log, QWidget *parent, RootLogfileDisplay& root) :
    QTabWidget(parent),
    ui(new Ui::LogsDisplay),
    log_handler(log),
    root(root)
{
    ui->setupUi(this);
    setObjectName(QString("MultiLogDisplay"));
    this->setContentsMargins(0, 0, 0, 0);
}

void LogsDisplay::applyGrep(grep_structure g) {
    auto active = currentWidget();
    if(active == nullptr) {
        return;
    }

    if(active->objectName() == QString("SingleLogDisplay")) {
        if(currentIndex() == 0) {
            newTab(log_handler.grep(g));
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

void LogsDisplay::newTab(logfile_proxy logfile) {
    if(parent() != nullptr && (count() == 0 || currentIndex() == 0)) {
        auto logDisplay = new SingleLogDisplay(logfile, this, root);
        auto newTab = addTab(logDisplay, logfile.name());
        setCurrentIndex(newTab);
    } else {
        const auto aliased = logfile.alias(QString("<base>"));
        auto newDisplay = new LogsDisplay(aliased, this, root);
        newDisplay->newTab(aliased);
        auto newTab = addTab(newDisplay, aliased.name());
        setCurrentIndex(newTab);
    }
    currentWidget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void LogsDisplay::scrollToLine(line_number_t line) {
    auto active = currentWidget();
    if(active == nullptr) {
        return;
    }

    if(active->objectName() == QString("SingleLogDisplay")) {
        dynamic_cast<SingleLogDisplay*>(active)->scrollToLine(line);
    } else if(active->objectName() == QString("MultiLogDisplay")) {
        dynamic_cast<LogsDisplay*>(active)->scrollToLine(line);
    }
}


LogsDisplay* LogsDisplay::mutateToNewTree() {
    auto newHandler = dynamic_cast<SingleLogDisplay*>(currentWidget())->logfile.alias("<base>");
    auto newDisplay = new LogsDisplay(newHandler, this, root);
    newDisplay->newTab(newHandler);

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