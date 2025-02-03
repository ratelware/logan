#ifndef DOC_SUPERVISOR_H
#define DOC_SUPERVISOR_H

#include <QStringList>
#include <list>
#include <memory>

#include "line_descriptor.h"
#include "logfile_handler.h"
#include "bookmark_t.h"

class doc_supervisor
{
public:
    doc_supervisor(QStringList file);

    logfile_handler& get_root() const;

    void add_bookmark(const bookmark_t &bookmark);
    const std::vector<bookmark_t>& get_bookmarks() const;
    void remove_bookmarks(const std::vector<line_number_t>&);
    void update_bookmark(line_length_t line, const bookmark_t &bookmark);

private:
    std::vector<QStringList> files_split_to_records;
    std::unique_ptr<logfile_handler> handler;

    std::vector<bookmark_t> bookmarks;
};

#endif // DOC_SUPERVISOR_H
