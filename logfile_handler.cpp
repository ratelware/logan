#include "logfile_handler.h"

logfile_handler::logfile_handler(QString name_, QStringList lines): lines(lines), fileName(name_)
{

}

QString logfile_handler::name() const {
    return fileName;
}
