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
    s.is_regex = this->ui->useRegex->isChecked();
    s.is_full_match = this->ui->matchFullWords->isChecked();
    s.is_case_sensitive = this->ui->caseSensitive->isChecked();
    s.is_reverse = this->ui->isReverse->isChecked();

    s.search_query = this->ui->searchQuery->text().toStdString();

    emit greppingRequested(s);
    this->hide();
}

void GrepWindow::cleanQuery() {
    this->ui->searchQuery->clear();
}

GrepWindow::~GrepWindow()
{
    delete ui;
}
