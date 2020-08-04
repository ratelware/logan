#ifndef LOGFILE_HANDLER_H
#define LOGFILE_HANDLER_H

#include <QStringList>

class logfile_handler
{
public:
    logfile_handler(QString name, QStringList lines);

    QString name() const;
    QStringList lines;

private:
    QString fileName;
};

#endif // LOGFILE_HANDLER_H
