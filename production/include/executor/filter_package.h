#ifndef FILTER_PACKAGE_H
#define FILTER_PACKAGE_H
#include <QIcon>
#include <QString>
#include <vector>

class QColor;

struct bookmark_template {
    QString prefix;
    QIcon icon;
};

struct tab_tree_node {
    std::unique_ptr<filter> selection_filter;
    std::vector<tab_tree_node> children;
};

struct filter_package {
    std::unordered_map<QString, QColor> highlights;
    std::unordered_map<QString, bookmark_template> bookmarks;
    tab_tree_node tab_tree;
};

#endif //FILTER_PACKAGE_H
