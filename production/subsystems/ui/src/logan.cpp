#include <QFile>
#include <QTextStream>
#include <QShortcut>
#include <QFileDialog>
#include <QTextDocumentFragment>

#include <memory>

#include <iostream>


#include "ui/logan.h"
#include "ui/logsdisplay.h"
#include "ui/openremotefiledialog.h"

#include "ui/singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

#include "ui/grepwindow.h"
#include "ui/aboutdialog.h"


#include "ui_logan.h"

Logan::Logan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logan)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":icons/racoon.png"));

    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_G), this)));
    shortcuts.push_back(std::unique_ptr<QShortcut>(new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this)));
    connect(shortcuts[0].get(), &QShortcut::activated, this, &Logan::displayGrepWindow);
    connect(shortcuts[1].get(), &QShortcut::activated, this, &Logan::displaySearchWindow);

    connect(&g, &GrepWindow::greppingRequested, ui->loganDisplay, &RootLogfileDisplay::applyGrepToCurrent);
    connect(&s, &SearchWindow::searchingRequested, ui->loganDisplay, &RootLogfileDisplay::applySearchToCurrent);
    connect(ui->actionAddLocalFile, &QAction::triggered, this, &Logan::openNewLocalFile);
    connect(ui->actionAddRemoteFile, &QAction::triggered, this, &Logan::openNewRemoteFile);

    connect(ui->actionGrep, &QAction::triggered, this, &Logan::displayGrepWindow);
    connect(ui->actionSearch, &QAction::triggered, this, &Logan::displaySearchWindow);

    connect(ui->actionClose, &QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &Logan::displayAboutWindow);

    connect(ui->actionNewProject, &QAction::triggered, this, &Logan::createNewProjectAction);
    connect(ui->actionOpenProject, &QAction::triggered, this, &Logan::openExistingProjectAction);

    statusBar()->showMessage(tr("Logan ready"));
}

void Logan::createNewProjectAction() {
    QFileDialog fileOpener(this);
    fileOpener.setFileMode(QFileDialog::Directory);
    connect(&fileOpener, &QFileDialog::fileSelected, this, &Logan::setActiveProjectLocation);
    fileOpener.exec();
}

void Logan::openExistingProjectAction() {
    QFileDialog fileOpener(this);
    fileOpener.setFileMode(QFileDialog::ExistingFile);
    fileOpener.setNameFilter("*.logan");
    connect(&fileOpener, &QFileDialog::fileSelected, this, &Logan::setActiveProjectLocation);
    fileOpener.exec();
}

void Logan::setActiveProjectLocation(QString location) {
    active_project_workspace = project_controller.set_up(location);
}

void Logan::openNewLocalFile() {
    QFileDialog fileOpener(this);
    connect(&fileOpener, &QFileDialog::fileSelected, ui->loganDisplay, &RootLogfileDisplay::fileSelected);
    fileOpener.setFileMode(QFileDialog::ExistingFile);
    fileOpener.exec();
}

void Logan::openNewRemoteFile() {
    OpenRemoteFileDialog remote(active_project_workspace, this);
    connect(&remote, &OpenRemoteFileDialog::remoteFileSelected, ui->loganDisplay, &RootLogfileDisplay::fileSelected);
    remote.exec();
}

void Logan::displayGrepWindow() {
    auto selectedText = getSelectedText();
    if(!g.hasFocus()) {
        g.startNewGrep();
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
        s.startNewSearch();
        s.setQuery(selectedText);
        s.show();
    }

    if(!s.hasFocus()) {
        s.startNewSearch();
        if(!selectedText.isEmpty()) {
            s.setQuery(selectedText);
        }

        s.activateWindow();
    }
}

void Logan::displayAboutWindow() {
    AboutDialog().exec();
}

Logan::~Logan()
{
    delete ui;
}

