#include "ui/grepwindow.h"
#include "ui_grepwindow.h"
GrepWindow::GrepWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrepWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":icons/filter.png"));

    connect(
                this->ui->grepApproved,
                &QPushButton::clicked,
                this,
                &GrepWindow::formGrep
                );

    connect(this->ui->grepRejected, &QPushButton::clicked, this, &GrepWindow::close);
}

void GrepWindow::formGrep() {
    grep_structure s;
    s.is_regex = ui->useRegex->isChecked();
    s.is_case_sensitive = ui->caseSensitive->isChecked();
    s.is_reverse = ui->isReverse->isChecked();

    s.search_query = ui->searchQuery->currentText();

    for(int i = 0; i < ui->searchQuery->count(); ++i) {
        if(ui->searchQuery->itemText(i) == s.search_query) {
            ui->searchQuery->removeItem(i);
            break;
        }
    }

    ui->searchQuery->addItem(s.search_query);

    if(!s.search_query.isEmpty()) {
        emit greppingRequested(s);
    }

    hide();
}

void GrepWindow::setQuery(QString query) {
    ui->searchQuery->setCurrentText(query);
}

void GrepWindow::cleanQuery() {
    ui->searchQuery->clear();
}

void GrepWindow::startNewGrep() {
    ui->searchQuery->setFocus(Qt::ActiveWindowFocusReason);
}

GrepWindow::~GrepWindow()
{
    delete ui;
}
