#include <QFile>
#include <QTextStream>
#include <QShortcut>
#include <QFileDialog>
#include <QTextDocumentFragment>

#include <memory>

#include <iostream>


#include "logan.h"
#include "logsdisplay.h"
#include "singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

#include "grepwindow.h"


#include "ui_logan.h"

Logan::Logan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logan)
{
    ui->setupUi(this);

    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_G), this)));
    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this)));
    connect(shortcuts[0].get(), &QShortcut::activated, this, &Logan::displayGrepWindow);
    connect(shortcuts[1].get(), &QShortcut::activated, this, &Logan::displaySearchWindow);

    connect(&g, &GrepWindow::greppingRequested, ui->loganDisplay, &RootLogfileDisplay::applyGrepToCurrent);
    connect(&s, &SearchWindow::searchingRequested, ui->loganDisplay, &RootLogfileDisplay::applySearchToCurrent);
    connect(ui->actionOpen, &QAction::triggered, this, &Logan::openNewFile);
}

void Logan::openNewFile() {
    QFileDialog fileOpener(this);
    connect(&fileOpener, &QFileDialog::fileSelected, ui->loganDisplay, &RootLogfileDisplay::fileSelected);
    fileOpener.setFileMode(QFileDialog::ExistingFile);
    fileOpener.exec();
}

void Logan::displayGrepWindow() {
    auto selectedText = getSelectedText();
    if(!g.hasFocus()) {
        g.setQuery(selectedText);
        g.show();
    }
}

QString Logan::getSelectedText() const {
    auto currentWidget = this->focusWidget();

    if(currentWidget->objectName() == QString("display") && currentWidget->parentWidget() != nullptr && currentWidget->parentWidget()->objectName() == QString("SingleLogDisplay")) {
        auto display = dynamic_cast<SingleLogDisplay*>(currentWidget->parentWidget());
        auto selected = display->ui->display->textCursor().selection().toPlainText();
        return selected;
    }

    return QString();
}

void Logan::displaySearchWindow() {
    auto selectedText = getSelectedText();
    if(!s.isVisible()) {
        s.setQuery(selectedText);
        s.show();
    }

    if(!s.hasFocus()) {
        if(!selectedText.isEmpty()) {
            s.setQuery(selectedText);
        }

        s.activateWindow();
    }
}

Logan::~Logan()
{
    delete ui;
}

