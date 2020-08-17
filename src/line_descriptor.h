#ifndef LINE_DESCRIPTOR_H
#define LINE_DESCRIPTOR_H

typedef unsigned int line_number_t;
typedef int block_number_t;
typedef unsigned int line_length_t;
typedef unsigned int doc_position_t;
typedef unsigned long doc_size_t;

struct line_descriptor {
    line_number_t line_number;
    line_length_t line_length;
    doc_size_t line_start;
};

#endif // LINE_DESCRIPTOR_H
