#ifndef LOGFILE_MANAGER_H
#define LOGFILE_MANAGER_H

#include <QString>
#include <QFile>
#include <QMap>

#include "logfile_handler.h"

class logfile_manager
{
public:
    logfile_manager();

    logfile_handler& open_file(const char* path);
    logfile_handler& open_file(const QString& path);

private:

    typedef int logfile_id;

    logfile_handler& new_handler(QFile&& file);

    QVector<logfile_handler> handlers;
};

#endif // LOGFILE_MANAGER_H
