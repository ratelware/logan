#ifndef LOGFILE_HANDLER_H
#define LOGFILE_HANDLER_H

#include <QStringList>

#include "grep_structure.h"

class logfile_manager;
class logfile_proxy;

class logfile_handler
{
public:
    logfile_handler(logfile_manager& parent, QStringList lines);

    logfile_proxy as(QString name);
    logfile_handler& grep(grep_structure g);

    QStringList lines;

private:
    logfile_manager& manager;
};

class logfile_proxy {
public:
    logfile_proxy(logfile_handler& handler, QString name);

    QString name() const;
    logfile_proxy alias(QString newName);

    const QStringList& lines() const;
    logfile_proxy grep(grep_structure s);

private:
    QString fileName;
    logfile_handler& handler;
};

#endif // LOGFILE_HANDLER_H
