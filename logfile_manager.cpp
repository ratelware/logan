#include "logfile_manager.h"

#include <QFile>
#include <QTextStream>

logfile_manager::logfile_manager()
{

}

doc_supervisor& logfile_manager::open_file(const char* path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw new std::runtime_error("Failed to open file");

    return new_supervisor(std::move(file));
}

doc_supervisor& logfile_manager::open_file(const QString& path) {
    return open_file(path.toStdString().c_str());
}

doc_supervisor& logfile_manager::new_supervisor(QFile&& file) {
    QTextStream in(&file);
    supervisors.push_back(doc_supervisor(in.readAll().split(QString("\n"))));
    return supervisors.back();
}
