#ifndef LOGFILE_MANAGER_H
#define LOGFILE_MANAGER_H

#include <QString>
#include <QFile>
#include <list>
#include <memory>

#include "doc_supervisor.h"
#include "logfile_handler.h"

class logfile_manager
{
public:
    logfile_manager();

    doc_supervisor& open_file(const char* path);
    doc_supervisor& open_file(const QString& path);
    doc_supervisor& new_supervisor(QFile&& file);
private:

    typedef int logfile_id;
    std::list<doc_supervisor> supervisors;
};

#endif // LOGFILE_MANAGER_H
