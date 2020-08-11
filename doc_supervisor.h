#ifndef DOC_SUPERVISOR_H
#define DOC_SUPERVISOR_H

#include <QStringList>
#include <list>
#include <memory>

#include "logfile_handler.h"

class doc_supervisor
{
public:
    doc_supervisor(QStringList file);

    logfile_handler& get_root();

private:
    std::vector<QStringList> files_split_to_records;
    std::vector<std::vector<long>> line_numbers;
    std::unique_ptr<logfile_handler> handler;

};

#endif // DOC_SUPERVISOR_H
