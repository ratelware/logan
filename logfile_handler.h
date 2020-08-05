#ifndef LOGFILE_HANDLER_H
#define LOGFILE_HANDLER_H

#include <QStringList>
#include <map>

#include "grep_structure.h"

class logfile_manager;
class logfile_proxy;

extern bool operator<(const grep_structure, const grep_structure);

class logfile_handler
{
public:
    logfile_handler(logfile_manager& parent, QStringList& contentByLines, std::vector<long> relevantLines);

    logfile_proxy as(QString name);
    logfile_handler& grep(grep_structure g);

    QString get_text();

private:
    QStringList& content;
    std::vector<long> relevantLines;

    logfile_manager& manager;
    std::map<grep_structure, logfile_handler> children;
};

class logfile_proxy {
public:
    logfile_proxy(logfile_handler& handler, QString name);

    QString name() const;
    logfile_proxy alias(QString newName);

    QString text() const;
    logfile_proxy grep(grep_structure s);

private:
    QString fileName;
    logfile_handler& handler;
};

#endif // LOGFILE_HANDLER_H
