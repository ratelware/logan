#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QObject>
#include <QListWidgetItem>

#include "line_descriptor.h"
#include "bookmark_structure.h"

class Bookmark : public QListWidgetItem
{
public:
    Bookmark(QListWidget* parent, bookmark_structure b);

    line_number_t getLine();

    bookmark_structure structure() const;

private:
    bookmark_structure b;
};

#endif // BOOKMARK_H
