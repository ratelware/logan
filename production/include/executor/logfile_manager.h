#ifndef LOGFILE_MANAGER_H
#define LOGFILE_MANAGER_H

#include <QString>
#include <QTextStream>
#include <QFile>
#include <list>
#include <memory>

#include "doc_supervisor.h"
#include "filter_package.h"
#include "logfile_handler.h"

class logfile_manager
{
public:
    logfile_manager();

    doc_supervisor& open_file(const char* path);
    doc_supervisor& open_file(const QString& path);
    doc_supervisor& new_supervisor(QTextStream&& file);
    doc_supervisor& supervisor_at(int index);

    [[nodiscard]] filter_package filters_for(const QString& path) const;

    void remove_supervisor(int index);
private:

    typedef int logfile_id;
    std::list<doc_supervisor> supervisors;
};

#endif // LOGFILE_MANAGER_H
