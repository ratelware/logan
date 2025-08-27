#include <QRegularExpression>

#include <executor/logfile_handler.h>
#include <executor/logfile_manager.h>

#include "executor/constants.h"

logfile_handler::logfile_handler(
        doc_supervisor& parent,
        QStringList& content_by_lines,
        std::vector<line_descriptor> lines
        )
    : content(content_by_lines),
      relevant_lines(lines),
      supervisor(parent)
{

}

doc_position_t logfile_handler::line_start_position(line_number_t l) const {
    auto item = std::lower_bound(relevant_lines.begin(), relevant_lines.end(), l, [](line_descriptor v1, line_number_t v2) {return v1.line_number < v2;});
    if(item == relevant_lines.end()) {
        return relevant_lines.size() > 0 ? relevant_lines.back().line_start : 0;
    }

    return item->line_start;
}

logfile_proxy logfile_handler::as(QString name) {
    return logfile_proxy(*this, name);
}

line_number_t logfile_handler::line_number(block_number_t block_number) const {
    return relevant_lines[block_number].line_number;
}

logfile_handler& logfile_handler::grep(std::unique_ptr<filter>&& g) {
    for(auto& c: children) {
        if(c.first->same_as(*g)) {
            return c.second;
        }
    }

    std::vector<line_descriptor> entries;
    std::for_each(relevant_lines.begin(), relevant_lines.end(), [&](line_descriptor d){
        if(g->matches(content[d.line_number], d.line_number)) {
            entries.push_back(line_descriptor{
                .line_number = d.line_number,
                .line_length = d.line_length,
                .line_start = entries.empty() ? 0 : entries.back().line_start + entries.back().line_length,
            });
        }
    });

    children.emplace_back(std::move(g), logfile_handler(supervisor, content, entries));
    return children.back().second;
}

void logfile_handler::add_line(line_number_t relevant_line) {
    auto new_loc = std::lower_bound(
        relevant_lines.begin(),
        relevant_lines.end(),
        relevant_line,
        [](line_descriptor line_desc, line_number_t line_num) {return line_desc.line_number < line_num;}
        );

    doc_size_t line_start = new_loc == relevant_lines.begin() ? 0 : (new_loc - 1)->line_start + (new_loc - 1)->line_length;

    auto inserted_location = relevant_lines.insert(new_loc, line_descriptor {
        .line_number = relevant_line,
        .line_length = static_cast<line_length_t>(content.at(relevant_line).length() + EOL.size()),
        .line_start = line_start,
    });

    for (auto it = inserted_location + 1; it != relevant_lines.end(); ++it) {
        auto prev = it - 1;
        it->line_start = prev->line_start + prev->line_length;
    }
}

QString logfile_handler::get_text() {
    QStringList l;
    std::for_each(relevant_lines.begin(), relevant_lines.end(), [&](line_descriptor t){
        l.push_back(content[t.line_number]);
    });

    return l.join("\n");
}

logfile_proxy::logfile_proxy(logfile_handler& h, QString name): fileName(name), handler(h) {
}

QString logfile_proxy::name() const {
    return fileName;
}

QString logfile_proxy::text() const {
    return handler.get_text();
}

line_number_t logfile_proxy::line_number(block_number_t at) const {
    return handler.line_number(at);
}

doc_position_t logfile_proxy::line_start_position(line_number_t l) const {
    return handler.line_start_position(l);
}

logfile_proxy logfile_proxy::alias(QString name) {
    return logfile_proxy(handler, name);
}

logfile_proxy logfile_proxy::grep(std::unique_ptr<filter>&& g) {
    QString name = g->name();
    logfile_handler& h = handler.grep(std::move(g));
    return logfile_proxy(h, name);
}
