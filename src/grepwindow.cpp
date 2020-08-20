#include "grepwindow.h"
#include "ui_grepwindow.h"
GrepWindow::GrepWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrepWindow)
{
    ui->setupUi(this);

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

    s.search_query = ui->searchQuery->text();

    emit greppingRequested(s);
    hide();
}

void GrepWindow::setQuery(QString query) {
    ui->searchQuery->setText(query);
}

void GrepWindow::cleanQuery() {
    ui->searchQuery->clear();
}

GrepWindow::~GrepWindow()
{
    delete ui;
}
