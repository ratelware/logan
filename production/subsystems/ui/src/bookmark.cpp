#include "ui/bookmark.h"

Bookmark::Bookmark(QListWidget* parent, bookmark_structure b): QListWidgetItem(parent), b(b)
{
    setText(b.bookmark_name);
    setIcon(b.icon);
}

line_number_t Bookmark::getLine() {
    return b.line_number;
}


bookmark_structure Bookmark::structure() const {
    return b;
}
