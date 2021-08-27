#include "ui/searchwindow.h"
#include "ui_searchwindow.h"

#include <QLineEdit>

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":icons/search.png"));

    connect(
                this->ui->searchApproved,
                &QPushButton::clicked,
                this,
                &SearchWindow::formSearch
                );

    connect(ui->searchRejected, &QPushButton::clicked, this, &SearchWindow::close);
}

void SearchWindow::formSearch() {
    search_structure s;
    s.is_regex = ui->useRegex->isChecked();
    s.is_case_sensitive = ui->caseSensitive->isChecked();
    s.search_parents = ui->searchParents->isChecked();
    s.is_backwards = ui->searchBackwards->isChecked();
    s.wrap_around = ui->wrapAround->isChecked();
    s.search_query = ui->searchQuery->currentText();

    bool found = false;
    for(int i = 0; i < ui->searchQuery->count(); ++i) {
        if(ui->searchQuery->itemText(i) == s.search_query) {
            found = true;
            break;
        }
    }

    if(!found) {
        ui->searchQuery->addItem(s.search_query);
    }

    if(!s.search_query.isEmpty()) {
        emit searchingRequested(s);
    }

}

void SearchWindow::startNewSearch() {
    ui->searchQuery->setFocus(Qt::ActiveWindowFocusReason);
}

void SearchWindow::cleanQuery() {
    this->ui->searchQuery->clear();
}

void SearchWindow::setQuery(QString query) {
    this->ui->searchQuery->setCurrentText(query);
    this->ui->searchQuery->lineEdit()->selectAll();
}

SearchWindow::~SearchWindow()
{
    delete ui;
}
