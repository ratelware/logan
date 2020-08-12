#include "bookmark.h"

Bookmark::Bookmark(QListWidget* parent, bookmark_structure b): QListWidgetItem(parent), b(b)
{
    setText(b.bookmark_name);
}

line_number_t Bookmark::getLine() {
    return b.line_number;
}
