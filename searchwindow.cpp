#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

    connect(
                this->ui->searchApproved,
                &QPushButton::clicked,
                this,
                &SearchWindow::formSearch
                );

    connect(this->ui->searchRejected, &QPushButton::clicked, this, &SearchWindow::close);

}

void SearchWindow::formSearch() {
    search_structure s;
    s.is_regex = ui->useRegex->isChecked();
    s.is_full_match = ui->matchFullWords->isChecked();
    s.is_case_sensitive = ui->caseSensitive->isChecked();
    s.search_parents = ui->searchParents->isChecked();
    s.is_backwards = ui->searchBackwards->isChecked();
    s.wrap_around = ui->wrapAround->isChecked();
    s.search_query = ui->searchQuery->text().toStdString();

    emit searchingRequested(s);
}

void SearchWindow::cleanQuery() {
    this->ui->searchQuery->clear();
}

SearchWindow::~SearchWindow()
{
    delete ui;
}
