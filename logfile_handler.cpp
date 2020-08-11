#include "logfile_handler.h"
#include "logfile_manager.h"

logfile_handler::logfile_handler(
        doc_supervisor& parent,
        QStringList& contentByLines,
        std::vector<long> lines
        )
    : content(contentByLines),
      relevantLines(lines),
      supervisor(parent)
{

}


logfile_proxy logfile_handler::as(QString name) {
    return logfile_proxy(*this, name);
}

logfile_handler& logfile_handler::grep(grep_structure g) {
    auto found = children.find(g);
    if(found != children.end()) {
        return found->second;
    }

    QString query = g.search_query;
    if(!g.is_case_sensitive) {
        query = query.toUpper();
    }

    std::vector<long> entries;
    std::for_each(relevantLines.begin(), relevantLines.end(), [&](long t){
        QString cmp = (g.is_case_sensitive) ? content[t] : content[t].toUpper();

        if(cmp.contains(query) ^ g.is_reverse) {
            entries.push_back(t);
        }
    });

    auto it = children.insert(std::make_pair(g, logfile_handler(supervisor, content, entries)));
    return it.first->second;
}

QString logfile_handler::get_text() {
    QStringList l;
    qDebug("Getting text from %lld lines.", relevantLines.size());
    std::for_each(relevantLines.begin(), relevantLines.end(), [&](long t){
        l.push_back(content[t]);
    });

    return l.join("\n");
}

bool operator<(const grep_structure g1, const grep_structure g2) {
    auto direct = g1.search_query.compare(g2.search_query);
    if(direct != 0) {
        return direct;
    }

    auto other_g1 = (g1.is_regex << 3) | (g1.is_reverse << 2) | (g1.is_full_match << 1) | (g1.is_case_sensitive << 0);
    auto other_g2 = (g2.is_regex << 3) | (g2.is_reverse << 2) | (g2.is_full_match << 1) | (g2.is_case_sensitive << 0);

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

logfile_proxy logfile_proxy::alias(QString name) {
    return logfile_proxy(handler, name);
}

logfile_proxy logfile_proxy::grep(grep_structure g) {
    logfile_handler& h = handler.grep(g);
    return logfile_proxy(h, g.search_query);
}
