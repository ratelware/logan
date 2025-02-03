#ifndef DOC_SUPERVISOR_H
#define DOC_SUPERVISOR_H

#include <memory>

#include "line_descriptor.h"
#include "logfile_handler.h"
#include "bookmark_t.h"
#include "filter_package.h"

class doc_supervisor
{
public:
    explicit doc_supervisor(QStringList file);

    [[nodiscard]] logfile_handler& get_root() const;

    void add_bookmark(const bookmark_t &bookmark);
    [[nodiscard]] const std::vector<bookmark_t>& get_bookmarks() const;
    void remove_bookmarks(const std::vector<line_number_t>&);
    void update_bookmark(line_length_t line, const bookmark_t &bookmark);

    void apply_filters(const filter_package& filters);

private:
    std::vector<QStringList> files_split_to_records;
    std::unique_ptr<logfile_handler> handler;

    std::vector<bookmark_t> bookmarks;
};

#endif // DOC_SUPERVISOR_H
