#ifndef BOOKMARK_STRUCTURE_H
#define BOOKMARK_STRUCTURE_H

#include <QString>
#include <QIcon>

#include "line_descriptor.h"

struct bookmark_t {
    line_number_t line_number;
    QString bookmark_name;
    QIcon icon;
};

#endif // BOOKMARK_STRUCTURE_H
