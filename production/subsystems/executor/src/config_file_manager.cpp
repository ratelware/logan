#include <executor/config_file_manager.h>
#include <executor/xml_selector.h>

#include <QFile>

const int UNUSED = 0;
const QString defaultConfig = ":/presets/configuration.xml";

config_file_manager::config_file_manager(const QString &initial_file) : schema(nullptr, &xmlSchemaFree)
{
    QFile schemaFile(":/presets/config-schema.xsd");
    if(!schemaFile.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open schema file");
        schemaFile.close();
        return;
    }


    xml_schema_loading_status status = load_xml_schema(schemaFile);
    schemaFile.close();

    if(status == xml_schema_loading_status::error) {
        return;
    }

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
        QByteArray docContent = file.readAll();
        auto ctx = xmlSchemaNewValidCtxt(schema.get());

        xmlDocPtr xmlDoc = xmlReadMemory(docContent.data(), docContent.size(), name.toStdString().c_str(), nullptr, UNUSED);
        int validationResult = xmlSchemaValidateDoc(ctx, xmlDoc);
        xmlSchemaFreeValidCtxt(ctx);
        xmlFreeDoc(xmlDoc);

        if(validationResult > 0) {
            file.close();
            qWarning(("Validation failed for file: " + name).toStdString().c_str());
            return;
        }

        if(validationResult < 0) {
            file.close();
            qWarning(("Failed to validate XML - cannot read " + name).toStdString().c_str());
            return;
        }

        if(!doc.setContent(docContent)) {
            qWarning(("Failed to load XML - cannot read " + name).toStdString().c_str());
        }

        file.close();
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
            load_doc(grandchild.toElement().text());
        }
    }

}

std::vector<QDomElement> config_file_manager::get_vector(xml_selector q) const {
    auto path = q.selector.split("/");
    std::vector<QDomElement> elems;

    for(auto d: documents) {
        std::vector<QDomElement> analysis;
        std::vector<QDomElement> nextAnalysis;
        analysis.push_back(d.second.documentElement());
        for(auto p: path) {
            while(!analysis.empty()) {
                QDomElement curr = analysis.back();
                analysis.pop_back();

                if(curr.isNull()) {
                    break;
                }

                QDomNodeList children = curr.childNodes();

                for(auto c = 0; c < children.size(); ++c) {
                    if(children.at(c).nodeName() == p) {
                        nextAnalysis.push_back(children.at(c).toElement());
                    }
                }
            }

            analysis = nextAnalysis;
            nextAnalysis = std::vector<QDomElement>();
        }

        for(auto a = analysis.begin(); a != analysis.end(); ++a) {
            elems.push_back(*a);
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
    return get_item(q).text();
}


bool config_file_manager::get_bool(xml_selector q) const {
    return get_string(q).toLower() == "true";
}

int config_file_manager::get_int(xml_selector q) const {
    return get_string(q).toInt();
}

xml_schema_loading_status config_file_manager::load_xml_schema(QFile& file) {

    QByteArray arr = file.readAll();
    xmlSchemaParserCtxtPtr parser = xmlSchemaNewMemParserCtxt(arr.data(), arr.count());
    if(parser == nullptr) {
        return xml_schema_loading_status::error;
    }

    schema.reset(xmlSchemaParse(parser));
    xmlSchemaFreeParserCtxt(parser);

    return schema.get() == nullptr ? xml_schema_loading_status::error : xml_schema_loading_status::success;
}
