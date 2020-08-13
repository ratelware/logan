#include "doc_supervisor.h"
#include <iterator>
#include <memory>

#include "constants.h"

doc_supervisor::doc_supervisor(QStringList file)
{
    std::vector<line_descriptor> file_lines = std::vector<line_descriptor>(file.length());
    for(std::size_t i = 0; i < file.length(); ++i) {
        file_lines[i].line_number = i;
        file_lines[i].line_length = file[i].length() + EOL.length();
        file_lines[i].line_start = (i == 0) ? 0 : file_lines[i - 1].line_start + file_lines[i - 1].line_length;
    }

    files_split_to_records.push_back(file);
    handler.reset(new logfile_handler(*this, files_split_to_records.back(), file_lines));
}

logfile_handler& doc_supervisor::get_root() {
    return *handler;
}

void doc_supervisor::add_bookmark(bookmark_structure b) {
    for(auto i = bookmarks.begin(); i != bookmarks.end(); ++i) {
        if(i->line_number > b.line_number) {
            bookmarks.insert(i, b);
            return;
        }
    }

    bookmarks.push_back(b);
}

const std::vector<bookmark_structure>& doc_supervisor::get_bookmarks() const {
    return bookmarks;
}
