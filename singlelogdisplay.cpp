#include "singlelogdisplay.h"
#include "ui_singlelogdisplay.h"

#include "logsdisplay.h"

#include <QAction>
#include <QClipboard>
#include <QTextDocumentFragment>
#include <QTextCursor>

SingleLogDisplay::SingleLogDisplay(QStringList& l, LogsDisplay *parent) :
    QWidget(parent),
    text(l),
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

    ui->display->setPlainText(text.join(QString("\n")));
}

void SingleLogDisplay::setUpActions() {
    auto copyAction = new QAction("Copy");
    auto bookmarkAction = new QAction("Bookmark");
    auto colourAction = new QAction("Make colorful");

    auto all = QList<QAction*>({copyAction, bookmarkAction, colourAction});

    connect(copyAction, &QAction::triggered, this, &SingleLogDisplay::copySelectionToClipboard);
    connect(colourAction, &QAction::triggered, this, &SingleLogDisplay::emphasiseSelection);

    insertActions(nullptr, all);
}

void SingleLogDisplay::copySelectionToClipboard() {
    QGuiApplication::clipboard()->setText(ui->display->textCursor().selection().toPlainText());
}

void SingleLogDisplay::emphasiseSelection() {
    auto cursor = ui->display->textCursor();
    auto selection = cursor.selection().toPlainText();

    ui->display->setTextCursor(cursor);

    int totalPos = 0;
    for(auto c: text) {
        auto index = c.indexOf(selection);
        while(index != -1) {
            auto tempCursor = ui->display->textCursor();
            tempCursor.setPosition(totalPos + index);
            tempCursor.setPosition(totalPos + index + selection.size(), QTextCursor::KeepAnchor);
            auto format = QTextCharFormat();
            format.setBackground(QBrush(Qt::green));
            tempCursor.setCharFormat(format);
            ui->display->setTextCursor(tempCursor);

            index = c.indexOf(selection, index + 1);
        }
        totalPos += c.size() + 1;
    }

    ui->display->setTextCursor(cursor);
}

void SingleLogDisplay::applySearch(search_structure s) {
    qDebug((std::string("Searching for ") + s.search_query).c_str());

    QStringList l;
    QString query = QString::fromStdString(s.search_query);
    if(!s.is_case_sensitive) {
        query = query.toUpper();
    }

    auto currentPosition = ui->display->textCursor().position();
    auto totalChars = 0;

    qDebug("Starting search at %d", currentPosition);
    for(auto& t : text) {
        totalChars = t.size() + totalChars + 1;
        if(totalChars  < currentPosition) {
            continue;
        }

        QString cmp = (s.is_case_sensitive) ? t : t.toUpper();

        auto start = cmp.indexOf(query);

        qDebug("Search of query finished at: %d", start);
        if(totalChars - t.size() + start - 1 == currentPosition - query.size()) {
            start = cmp.indexOf(query, start + 1);
        }

        if(start != -1) {
            QTextCursor c = ui->display->textCursor();
            c.setPosition(totalChars - 1 - t.size() + start);
            c.setPosition(totalChars - 1 - t.size() + start + query.size(), QTextCursor::KeepAnchor);
            ui->display->setTextCursor(c);

            qDebug("Selecting characters between %d and %d", totalChars - 1 - t.size() + start, totalChars - 1 - t.size() + start + query.size());

            break;
        }
    }
}


SingleLogDisplay::~SingleLogDisplay()
{
    delete ui;
}
