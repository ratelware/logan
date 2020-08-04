#ifndef FIND_STRUCTURE_H
#define FIND_STRUCTURE_H

#include <QString>

struct search_structure {
    QString search_query;
    bool is_regex;
    bool is_case_sensitive;
    bool is_full_match;
    bool is_backwards;
    bool search_parents;
    bool wrap_around;
};

#endif // FIND_STRUCTURE_H
