#include "config_file_manager.h"
#include "xml_selector.h"

#include <QFile>
#include <QXmlSchemaValidator>

const QString defaultConfig = ":/presets/configuration.xml";

config_file_manager::config_file_manager(QString initial_file)
{
    QFile schemaFile(":/presets/config-schema.xsd");
    if(!schemaFile.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open schema file");
    }

    if(!schema.load(&schemaFile)) {
        qWarning("Schema file invalid!");
    }
    schemaFile.close();

    if(initial_file != "") {
        load_doc(initial_file);
    }

    load_doc(defaultConfig);
}

void config_file_manager::load_doc(QString name) {

    if(std::any_of(documents.begin(), documents.end(), [&name](std::pair<QString, QDomDocument>& t){return t.first == name; })) {
        return;
    }

    QDomDocument doc(name);
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning(("Failed to open file " + name).toStdString().c_str());
        return;
    } else {
        QXmlSchemaValidator validator(schema);
        if(!validator.validate(&file)) {
            qWarning(("Validation failed when reading file: " + name).toStdString().c_str());
            return;
        }

        if(!doc.setContent(&file)) {
            file.close();
            qWarning(("Failed to load XML from file " + name).toStdString().c_str());
            return;
        }
    }

    documents.push_back(std::make_pair(name, doc));

    auto child = doc.documentElement().namedItem("parents");
    if(child.isNull()) {
        return;
    }

    auto grandchildren = child.childNodes();
    for(int j = 0; j < grandchildren.count(); ++j) {
        auto grandchild = grandchildren.at(j);
        if(grandchild.nodeName() == "parent") {
            load_doc(grandchild.nodeValue());
        }
    }

}

std::vector<QDomElement> config_file_manager::get_vector(xml_selector q) const {
    auto path = q.selector.split("/");
    std::vector<QDomElement> elems;

    for(auto d: documents) {
        auto curr = d.second.documentElement();
        for(auto p: path) {
            if(curr.isNull()) {
                break;
            }

            curr.namedItem(p);
        }

        if(!curr.isNull()) {
            elems.push_back(curr);
        }
    }

    return elems;
}

QDomElement config_file_manager::get_item(xml_selector q) const {
    auto path = q.selector.split("/");
    for(auto d: documents) {
        auto curr = d.second.documentElement();
        for(auto p: path) {
            if(curr.isNull()) {
                break;
            }

            curr.namedItem(p);
        }

        if(!curr.isNull()) {
            return curr;
        }
    }

    return QDomElement();
}

QString config_file_manager::get_string(xml_selector q) const {
    return get_item(q).nodeValue();
}


bool config_file_manager::get_bool(xml_selector q) const {
    return get_string(q).toLower() == "true";
}

int config_file_manager::get_int(xml_selector q) const {
    return get_string(q).toInt();
}

