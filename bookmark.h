#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QObject>
#include <QListWidgetItem>

#include "bookmark_structure.h"

class Bookmark : public QListWidgetItem
{
public:
    Bookmark(bookmark_structure b);

private:
    bookmark_structure b;
};

#endif // BOOKMARK_H
