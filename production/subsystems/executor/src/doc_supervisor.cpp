#include <executor/doc_supervisor.h>
#include <iterator>
#include <memory>
#include <algorithm>
#include <any>

#include <executor/constants.h>

doc_supervisor::doc_supervisor(QStringList file)
{
    std::vector<line_descriptor> file_lines = std::vector<line_descriptor>(file.length());
    for(qsizetype i = 0; i < file.length(); ++i) {
        file_lines[i].line_number = i;
        file_lines[i].line_length = file[i].length() + EOL.length();
        file_lines[i].line_start = (i == 0) ? 0 : file_lines[i - 1].line_start + file_lines[i - 1].line_length;
    }

    files_split_to_records.push_back(file);
    handler = std::make_unique<logfile_handler>(*this, files_split_to_records.back(), file_lines);
}

logfile_handler& doc_supervisor::get_root() const {
    return *handler;
}

void doc_supervisor::add_bookmark(const bookmark_t &b) {
    for(auto i = bookmarks.begin(); i != bookmarks.end(); ++i) {
        if(i->line_number > b.line_number) {
            bookmarks.insert(i, b);
            return;
        }
    }

    bookmarks.push_back(b);
}

const std::vector<bookmark_t>& doc_supervisor::get_bookmarks() const {
    return bookmarks;
}

void doc_supervisor::remove_bookmarks(const std::vector<line_number_t> & removed) {
    bookmarks.erase(
        std::remove_if(bookmarks.begin(), bookmarks.end(), [&removed](bookmark_t& b) {
            return std::any_of(removed.begin(), removed.end(), [&b](const line_number_t l) { return l == b.line_number; });
    }),
    bookmarks.end()
            );
}


void doc_supervisor::update_bookmark(line_number_t line, const bookmark_t &bookmark) {
    for(auto& b : bookmarks) {
        if(b.line_number == line) {
            b.bookmark_name = bookmark.bookmark_name;
            b.icon = bookmark.icon;
            return;
        }
    }
}

void doc_supervisor::apply_filters(const filter_package &filters) {

}
