#include "singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

#include "logsdisplay.h"

#include <QAction>
#include <QClipboard>
#include <QTextDocumentFragment>
#include <QTextCursor>
#include <QMessageBox>

SingleLogDisplay::SingleLogDisplay(logfile_proxy l, LogsDisplay *parent, RootLogfileDisplay& root) :
    QWidget(parent),
    logfile(l),
    ui(new Ui::SingleLogDisplay),
    root(root)
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

    // Set selection colors
    // Stolen from:
    QPalette p = ui->display->palette();
    p.setColor(QPalette::Highlight, Qt::yellow);
    p.setColor(QPalette::HighlightedText, Qt::black);
    ui->display->setPalette(p);
}

void SingleLogDisplay::setUpActions() {
    auto copyAction = new QAction("Copy");
    auto bookmarkAction = new QAction("Named bookmark");
    auto fastBookmarkAction = new QAction("Fast bookmark");
    auto colourAction = new QAction("Make colorful");

    auto all = QList<QAction*>({copyAction, bookmarkAction, colourAction});

    connect(copyAction, &QAction::triggered, this, &SingleLogDisplay::copySelectionToClipboard);
    connect(colourAction, &QAction::triggered, this, &SingleLogDisplay::emphasiseSelection);
    connect(bookmarkAction, &QAction::triggered, this, &SingleLogDisplay::bookmark);
    connect(fastBookmarkAction, &QAction::triggered, this, &SingleLogDisplay::fastBookmark);

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
    QString text = ui->display->toPlainText();
    auto start = s.is_backwards ?
                text.lastIndexOf(s.search_query, ui->display->textCursor().selectionStart() - 1, s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive) :
                text.indexOf(s.search_query, ui->display->textCursor().selectionEnd(), s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);

    if(start != -1) {
        QTextCursor c = ui->display->textCursor();
        c.setPosition(start);
        c.setPosition(start + s.search_query.size(), QTextCursor::KeepAnchor);
        ui->display->setTextCursor(c);
        return;
    } else if(s.wrap_around) {
        auto newStart = s.is_backwards ?
            text.lastIndexOf(s.search_query, -1, s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive) :
            text.indexOf(s.search_query, 0, s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);

        if(newStart != -1) {
            QTextCursor c = ui->display->textCursor();
            c.setPosition(newStart);
            c.setPosition(newStart + s.search_query.size(), QTextCursor::KeepAnchor);
            ui->display->setTextCursor(c);
            return;
        }
    }

    QMessageBox::warning(this, tr("Phrase not found"), tr("Failed to find searched phrase"));
}

void SingleLogDisplay::scrollToLine(line_number_t line) {
    auto location = logfile.line_start_position(line);
    auto cursor = ui->display->textCursor();
    cursor.setPosition(location);
    cursor.select(QTextCursor::BlockUnderCursor);

    ui->display->moveCursor(QTextCursor::End);
    ui->display->setTextCursor(cursor);
}

void SingleLogDisplay::bookmark() {
    fastBookmark();
}

void SingleLogDisplay::fastBookmark() {
    root.addBookmarkToCurrent(logfile.line_number(ui->display->textCursor().blockNumber()));
}

SingleLogDisplay::~SingleLogDisplay()
{
    delete ui;
}
