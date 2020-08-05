#include "singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

#include "logsdisplay.h"

#include <QAction>
#include <QClipboard>
#include <QTextDocumentFragment>
#include <QTextCursor>

SingleLogDisplay::SingleLogDisplay(logfile_proxy l, LogsDisplay *parent) :
    QWidget(parent),
    logfile(l),
    ui(new Ui::SingleLogDisplay)
{
    ui->setupUi(this);

    setUpActions();

    setObjectName(QString("SingleLogDisplay"));


    ui->display->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    ui->display->setWordWrapMode(QTextOption::NoWrap);
    ui->display->setReadOnly(true);
    ui->display->setTextInteractionFlags(ui->display->textInteractionFlags() | Qt::TextSelectableByKeyboard);

    ui->display->setOverwriteMode(false);

    ui->display->setPlainText(logfile.text());
}

void SingleLogDisplay::setUpActions() {
    auto copyAction = new QAction("Copy");
    auto bookmarkAction = new QAction("Bookmark");
    auto colourAction = new QAction("Make colorful");

    auto all = QList<QAction*>({copyAction, bookmarkAction, colourAction});

    connect(copyAction, &QAction::triggered, this, &SingleLogDisplay::copySelectionToClipboard);
    connect(colourAction, &QAction::triggered, this, &SingleLogDisplay::emphasiseSelection);
    connect(bookmarkAction, &QAction::triggered, this, &SingleLogDisplay::bookmark);

    insertActions(nullptr, all);
}

void SingleLogDisplay::copySelectionToClipboard() {
    QGuiApplication::clipboard()->setText(ui->display->textCursor().selection().toPlainText());
}

void SingleLogDisplay::emphasiseSelection() {
    auto cursor = ui->display->textCursor();
    auto selection = cursor.selection().toPlainText();

    ui->display->setTextCursor(cursor);

    QString text = ui->display->toPlainText();
    int finalPos = text.indexOf(selection);

    while(finalPos != -1) {
        QTextCursor c = ui->display->textCursor();
        c.setPosition(finalPos);
        c.setPosition(finalPos + selection.size(), QTextCursor::KeepAnchor);
        auto format = QTextCharFormat();
        format.setBackground(QBrush(Qt::green));
        c.setCharFormat(format);

        ui->display->setTextCursor(c);
        finalPos = text.indexOf(selection, finalPos + 1);

    }

    ui->display->setTextCursor(cursor);
}

void SingleLogDisplay::applySearch(search_structure s) {
    QStringList l;
    QString query = s.search_query;

    auto currentPosition = ui->display->textCursor().position();
    QString text = ui->display->toPlainText();

    auto start = text.indexOf(query, currentPosition + 1);

    if(start != -1) {
        QTextCursor c = ui->display->textCursor();
        c.setPosition(start);
        c.setPosition(start + query.size(), QTextCursor::KeepAnchor);
        ui->display->setTextCursor(c);
    }
}

void SingleLogDisplay::bookmark() {

}

SingleLogDisplay::~SingleLogDisplay()
{
    delete ui;
}
