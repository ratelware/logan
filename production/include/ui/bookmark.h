#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QObject>
#include <QListWidgetItem>

#include <executor/line_descriptor.h>
#include <executor/bookmark_t.h>

class Bookmark : public QListWidgetItem
{
public:
    Bookmark(QListWidget* parent, bookmark_t b);

    line_number_t getLine();

    bookmark_t structure() const;

private:
    bookmark_t b;
};

#endif // BOOKMARK_H
