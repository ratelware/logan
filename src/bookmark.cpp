#include "bookmark.h"

Bookmark::Bookmark(QListWidget* parent, bookmark_structure b): QListWidgetItem(parent), b(b)
{
    setText(b.bookmark_name);
    if(b.bookmark_name.toLower().contains("error")) {
        setIcon(QIcon(":icons/fail.png"));
    } else if(b.bookmark_name.toLower().contains("warn")) {
        setIcon(QIcon(":icons/warn.png"));
    } else if(b.bookmark_name.toLower().contains("info")) {
        setIcon(QIcon(":icons/info.png"));
    } else if(b.bookmark_name.toLower().contains("debug")) {
        setIcon(QIcon());
    } else if(b.bookmark_name.toLower().contains("trace")) {
        setIcon(QIcon(":icons/footprints.png"));
    } else {
        setIcon(QIcon());
    }
}

line_number_t Bookmark::getLine() {
    return b.line_number;
}
