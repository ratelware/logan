#ifndef GREP_STRUCTURE_H
#define GREP_STRUCTURE_H

#include <QString>

struct grep_structure {
    QString search_query;
    bool is_regex;
    bool is_case_sensitive;
    bool is_reverse;
};

#endif // GREP_STRUCTURE_H
