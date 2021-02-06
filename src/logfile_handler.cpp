#include <QRegularExpression>

#include "logfile_handler.h"
#include "logfile_manager.h"

logfile_handler::logfile_handler(
        doc_supervisor& parent,
        QStringList& contentByLines,
        std::vector<line_descriptor> lines
        )
    : content(contentByLines),
      relevantLines(lines),
      supervisor(parent)
{

}

doc_position_t logfile_handler::line_start_position(line_number_t l) const {
    auto item = std::lower_bound(relevantLines.begin(), relevantLines.end(), l, [](line_descriptor v1, line_number_t v2) {return v1.line_number < v2;});
    if(item == relevantLines.end()) {
        return relevantLines.size() > 0 ? relevantLines.back().line_start : 0;
    }

    return item->line_start;
}

logfile_proxy logfile_handler::as(QString name) {
    return logfile_proxy(*this, name);
}

line_number_t logfile_handler::line_number(block_number_t block_number) const {
    return relevantLines[block_number].line_number;
}

logfile_handler& logfile_handler::grep(grep_structure g) {
    auto found = children.find(g);
    if(found != children.end()) {
        return found->second;
    }

    QRegularExpression regexp(g.search_query, (g.is_case_sensitive) ? QRegularExpression::NoPatternOption : QRegularExpression::CaseInsensitiveOption);
    regexp.optimize();

    std::vector<line_descriptor> entries;
    std::for_each(relevantLines.begin(), relevantLines.end(), [&](line_descriptor d){
        if(regexp.match(content[d.line_number]).hasMatch() ^ g.is_reverse) {
            line_descriptor new_descriptor;
            new_descriptor.line_length = d.line_length;
            new_descriptor.line_start = entries.empty() ? 0 : entries.back().line_start + entries.back().line_length;
            new_descriptor.line_number = d.line_number;
            entries.push_back(new_descriptor);
        }
    });

    auto it = children.insert(std::make_pair(g, logfile_handler(supervisor, content, entries)));
    return it.first->second;
}

QString logfile_handler::get_text() {
    QStringList l;
    std::for_each(relevantLines.begin(), relevantLines.end(), [&](line_descriptor t){
        l.push_back(content[t.line_number]);
    });

    return l.join("\n");
}

bool operator<(const grep_structure g1, const grep_structure g2) {
    auto direct = g1.search_query.compare(g2.search_query);
    if(direct != 0) {
        return direct;
    }

    auto other_g1 = (g1.is_regex << 3) | (g1.is_reverse << 2) | (g1.is_case_sensitive << 1);
    auto other_g2 = (g2.is_regex << 3) | (g2.is_reverse << 2) | (g2.is_case_sensitive << 1);

    return other_g1 < other_g2;
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

logfile_proxy logfile_proxy::grep(grep_structure g) {
    logfile_handler& h = handler.grep(g);
    return logfile_proxy(h, g.search_query);
}
