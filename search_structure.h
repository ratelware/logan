#ifndef FIND_STRUCTURE_H
#define FIND_STRUCTURE_H

#include <string>

struct search_structure {
    std::string search_query;
    bool is_regex;
    bool is_case_sensitive;
    bool is_full_match;
    bool is_backwards;
    bool search_parents;
    bool wrap_around;
};

#endif // FIND_STRUCTURE_H
