#include "logfile_handler.h"
#include "logfile_manager.h"

logfile_handler::logfile_handler(logfile_manager& mgr, QStringList lines): lines(lines), manager(mgr)
{

}

logfile_proxy logfile_handler::as(QString name) {
    return logfile_proxy(*this, name);
}

logfile_handler& logfile_handler::grep(grep_structure g) {
    QStringList l;
    QString query = g.search_query;
    if(!g.is_case_sensitive) {
        query = query.toUpper();
    }

    std::for_each(lines.begin(), lines.end(), [&](QString t){
        QString cmp = (g.is_case_sensitive) ? t : t.toUpper();

        if(cmp.contains(query) ^ g.is_reverse) {
            l.push_back(t);
        }
    });

    return manager.manage_handler(new logfile_handler(manager, l));
}

logfile_proxy::logfile_proxy(logfile_handler& h, QString name): fileName(name), handler(h) {
}

QString logfile_proxy::name() const {
    return fileName;
}

const QStringList& logfile_proxy::lines() const {
    return handler.lines;
}

logfile_proxy logfile_proxy::alias(QString name) {
    return logfile_proxy(handler, name);
}

logfile_proxy logfile_proxy::grep(grep_structure g) {
    logfile_handler& h = handler.grep(g);
    return logfile_proxy(h, g.search_query);
}
