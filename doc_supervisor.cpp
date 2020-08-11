#include "doc_supervisor.h"
#include <iterator>
#include <memory>

doc_supervisor::doc_supervisor(QStringList file)
{
    files_split_to_records.push_back(file);
    std::vector<long> file_lines = std::vector<long>(file.length());
    std::iota(file_lines.begin(), file_lines.end(), 0);
    line_numbers.push_back(std::move(file_lines));
    handler.reset(new logfile_handler(*this, files_split_to_records.back(), line_numbers.back()));
}

logfile_handler& doc_supervisor::get_root() {
    return *handler;
}
