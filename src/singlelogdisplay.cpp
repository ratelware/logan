#include "singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

#include "logsdisplay.h"
#include "emphasis_color_manager.h"

#include <QAction>
#include <QClipboard>
#include <QTextDocumentFragment>
#include <QTextCursor>
#include <QTextBlock>
#include <QMessageBox>
#include <QInputDialog>

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

    auto all = QList<QAction*>({copyAction, bookmarkAction, fastBookmarkAction, colourAction});

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

    auto emphasisFormat = QTextCharFormat();
    emphasisFormat.setBackground(QBrush(emphasis_color_manager::get_instance().get_next_color(this)));
    while(finalPos != -1) {
        QTextCursor c = ui->display->textCursor();
        c.setPosition(finalPos);
        c.setPosition(finalPos + selection.size(), QTextCursor::KeepAnchor);
        c.setCharFormat(emphasisFormat);

        ui->display->setTextCursor(c);
        finalPos = text.indexOf(selection, finalPos + 1);

    }

    ui->display->setTextCursor(cursor);
}

void SingleLogDisplay::applySearch(search_structure s) {
    QString text = ui->display->toPlainText();
    int start = -1;
    int end = -1;

    if(s.is_regex) {
        QRegularExpression regex(s.search_query,  (s.is_case_sensitive) ? QRegularExpression::NoPatternOption : QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch m;
        regex.optimize();
        start = s.is_backwards ?
                text.lastIndexOf(regex, ui->display->textCursor().selectionStart() - 1, &m) :
                text.indexOf(regex, ui->display->textCursor().selectionEnd(), &m);

        end = m.capturedEnd();

    } else {
        start = s.is_backwards ?
                text.lastIndexOf(s.search_query, ui->display->textCursor().selectionStart() - 1, s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive) :
                text.indexOf(s.search_query, ui->display->textCursor().selectionEnd(), s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);

        end = start + s.search_query.length();
    }

    if(start != -1) {
        QTextCursor c = ui->display->textCursor();
        c.setPosition(start);
        c.setPosition(end, QTextCursor::KeepAnchor);
        ui->display->setTextCursor(c);
        return;
    } else if(s.wrap_around) {
        int newStart = -1;
        int newEnd = -1;
        if(s.is_regex) {
            QRegularExpression regex(s.search_query,  (s.is_case_sensitive) ? QRegularExpression::NoPatternOption : QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch m;
            regex.optimize();
            newStart = s.is_backwards ?
                    text.lastIndexOf(regex, -1, &m) :
                    text.indexOf(regex, 0, &m);

            newEnd = m.capturedEnd();
        } else {
            newStart = s.is_backwards ?
                    text.lastIndexOf(s.search_query, - 1, s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive) :
                    text.indexOf(s.search_query, 0, s.is_case_sensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
            newEnd = newStart + s.search_query.length();
        }

        if(newStart != -1) {
            QTextCursor c = ui->display->textCursor();
            c.setPosition(newStart);
            c.setPosition(newEnd, QTextCursor::KeepAnchor);
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
    cursor.select(QTextCursor::LineUnderCursor);

    ui->display->setTextCursor(cursor);
}

void SingleLogDisplay::bookmark() {
    bool ok = false;
    QString bookmarkName = QInputDialog::getText(this, tr("Add bookmark"), tr("Bookmark name"), QLineEdit::Normal, ui->display->textCursor().block().text(), &ok);
    if(ok && !bookmarkName.isEmpty()) {
        bookmark_structure b;
        b.line_number = logfile.line_number(ui->display->textCursor().blockNumber());
        b.bookmark_name = bookmarkName;
        root.addBookmarkToCurrent(b);
    }
}

void SingleLogDisplay::fastBookmark() {
    bookmark_structure b;
    b.line_number = logfile.line_number(ui->display->textCursor().blockNumber());
    b.bookmark_name = ui->display->textCursor().block().text();
    root.addBookmarkToCurrent(b);
}

SingleLogDisplay::~SingleLogDisplay()
{
    delete ui;
}