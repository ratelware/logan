#ifndef LOGFILE_HANDLER_H
#define LOGFILE_HANDLER_H

#include <QStringList>
#include <map>

#include "line_descriptor.h"
#include "grep_structure.h"

class doc_supervisor;
class logfile_proxy;

class logfile_handler
{
public:
    logfile_handler(doc_supervisor& parent, QStringList& contentByLines, std::vector<line_descriptor> relevantLines);

    logfile_proxy as(QString name);
    logfile_handler& grep(std::unique_ptr<filter>&& g);

    QString get_text();
    line_number_t line_number(block_number_t block_number) const;
    doc_position_t line_start_position(line_number_t line) const;

private:
    QStringList& content;
    std::vector<line_descriptor> relevantLines;

    doc_supervisor& supervisor;

    typedef std::pair<std::unique_ptr<filter>, logfile_handler> child_handler;
    std::vector<child_handler> children;
};

class logfile_proxy {
public:
    logfile_proxy(logfile_handler& handler, QString name);

    QString name() const;
    logfile_proxy alias(QString newName);

    QString text() const;
    logfile_proxy grep(std::unique_ptr<filter>&& s);

    line_number_t line_number(block_number_t block_number) const;
    doc_position_t line_start_position(line_number_t line) const;

private:
    QString fileName;
    logfile_handler& handler;
};

#endif // LOGFILE_HANDLER_H
