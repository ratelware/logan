#include <executor/logfile_manager.h>

#include <QFile>
#include <QTextStream>

#include <archive.h>
#include <archive_entry.h>

const int BUFFER_SIZE = 64 * 1024;

QByteArray archive_uncompress(const char* path) {
    QByteArray content;
    char buffer[BUFFER_SIZE];

    int result;
    struct archive* a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    archive_read_support_format_raw(a);
    result = archive_read_open_filename(a, path, BUFFER_SIZE);

    if(result != ARCHIVE_OK) {
        throw std::runtime_error("Cannot open archive");
    }

    struct archive_entry* ae;
    while(true) {
        result = archive_read_next_header(a, &ae);
        if(result == ARCHIVE_EOF) {
            break;
        }

        if(result != ARCHIVE_OK) {
            throw std::runtime_error("Cannot read archive entry");
        }

        qDebug("Extracting file: %s", archive_entry_pathname(ae));

        ssize_t size;
        while(true) {
            size = archive_read_data(a, buffer, BUFFER_SIZE);
            if(size < 0) {
                throw std::runtime_error("Reading archive entry failed");
            }

            if(size == 0) {
                break;
            }

            content.append(buffer, size);
        }
    }

    archive_read_close(a);
    archive_read_free(a);

    return content;
}

bool is_compressed(QString file) {
    return file.endsWith(".tar") ||
            file.endsWith(".gz") ||
            file.endsWith(".tgz") ||
            file.endsWith(".zip") ||
            file.endsWith(".bz2") ||
            file.endsWith(".xz") ||
            file.endsWith(".7z");
}

logfile_manager::logfile_manager()
{

}

void logfile_manager::remove_supervisor(int index) {
    supervisors.erase(std::next(supervisors.begin(), index));
}

doc_supervisor& logfile_manager::open_file(const char* path) {
    QString name(path);
    if(is_compressed(name)) {
        QTextStream buffer(archive_uncompress(path));
        return new_supervisor(std::move(buffer));
    } else {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw new std::runtime_error("Failed to open file");
        return new_supervisor(QTextStream(&file));
    }
}

doc_supervisor& logfile_manager::open_file(const QString& path) {
    return open_file(path.toStdString().c_str());
}

doc_supervisor& logfile_manager::new_supervisor(QTextStream&& file) {
    supervisors.emplace_back(file.readAll().split(QString("\n")));
    return supervisors.back();
}

doc_supervisor& logfile_manager::supervisor_at(int index) {
    return *(std::next(supervisors.begin(), index));
}
