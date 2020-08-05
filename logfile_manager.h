#ifndef LOGFILE_MANAGER_H
#define LOGFILE_MANAGER_H

#include <QString>
#include <QFile>
#include <list>
#include <memory>

#include "logfile_handler.h"

class logfile_manager
{
public:
    logfile_manager();

    logfile_handler& open_file(const char* path);
    logfile_handler& open_file(const QString& path);
    logfile_handler& new_handler(QFile&& file);
private:

    typedef int logfile_id;
    std::list<QStringList> files_split_to_records;
    std::list<logfile_handler> handlers;
};

#endif // LOGFILE_MANAGER_H
