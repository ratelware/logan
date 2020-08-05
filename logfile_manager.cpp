#include "logfile_manager.h"

#include <QFile>
#include <QTextStream>

logfile_manager::logfile_manager()
{

}

logfile_handler& logfile_manager::open_file(const char* path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw new std::runtime_error("Failed to open file");

    return new_handler(std::move(file));
}

logfile_handler& logfile_manager::open_file(const QString& path) {
    return open_file(path.toStdString().c_str());
}

logfile_handler& logfile_manager::new_handler(QFile&& file) {
    QTextStream in(&file);
    files_split_to_records.push_back(in.readAll().split(QString("\n")));

    std::vector<long> line_numbers(files_split_to_records.back().length());
    std::iota(line_numbers.begin(), line_numbers.end(), 0);
    handlers.push_back(logfile_handler(*this, files_split_to_records.back(), line_numbers));
    return handlers.back();
}
