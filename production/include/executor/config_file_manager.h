#ifndef CONFIG_FILE_MANAGER_H
#define CONFIG_FILE_MANAGER_H

#include "xml_selector.h"

#include <QString>
#include <QFile>
#include <QDomDocument>

#include <vector>
#include <functional>
#include <algorithm>

#include <libxml/xmlschemas.h>

enum xml_schema_loading_status {
    success,
    error
};

class config_file_manager
{
public:
    config_file_manager(QString initial_file);

    int get_int(xml_selector q) const;
    bool get_bool(xml_selector q) const;
    QString get_string(xml_selector q) const;

    template <typename T>
    T get_t(xml_selector q, std::function<T(QDomElement)> converter) const {
        return converter(get_item(q));
    }

    template <typename T>
    std::vector<T> get_vector_of(xml_selector q, std::function<T(QDomElement)> converter) const {
        auto items = get_vector(q);
        auto elems = std::vector<T>();
        elems.resize(items.size());
        std::transform(items.begin(), items.end(), elems.begin(), [&converter](QDomElement e) {
            return converter(e);
        });

        return elems;
    }

private:
    std::vector<std::pair<QString, QDomDocument> > documents;
    std::unique_ptr<xmlSchema, void(*)(xmlSchemaPtr)> schema;

    std::vector<QDomElement> get_vector(xml_selector q) const;
    QDomElement get_item(xml_selector q) const;

    void load_doc(QString name);
    xml_schema_loading_status load_xml_schema(QFile& file);
};

#endif // CONFIG_FILE_MANAGER_H
