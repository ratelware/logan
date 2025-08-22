#include <QRegularExpression>

#include <executor/logfile_handler.h>
#include <executor/logfile_manager.h>

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

logfile_handler& logfile_handler::grep(std::unique_ptr<filter>&& g) {
    for(auto& c: children) {
        if(c.first->same_as(*g)) {
            return c.second;
        }
    }

    std::vector<line_descriptor> entries;
    std::for_each(relevantLines.begin(), relevantLines.end(), [&](line_descriptor d){
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

QString logfile_handler::get_text() {
    QStringList l;
    std::for_each(relevantLines.begin(), relevantLines.end(), [&](line_descriptor t){
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
