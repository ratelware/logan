#ifndef BOOKMARK_STRUCTURE_H
#define BOOKMARK_STRUCTURE_H

#include <QString>

#include "line_descriptor.h"

struct bookmark_structure {
    line_number_t line_number;
    QString bookmark_name;
};

#endif // BOOKMARK_STRUCTURE_H
