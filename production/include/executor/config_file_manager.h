#ifndef CONFIG_FILE_MANAGER_H
#define CONFIG_FILE_MANAGER_H

#include "field_selector.h"

#include <QString>
#include <QFile>
#include <QDomDocument>

#include <vector>
#include <functional>
#include <algorithm>

#include <libxml/xmlschemas.h>
#include <chaiscript/chaiscript.hpp>

namespace config {
    struct grep {
        bool is_regex;
        bool is_inverse;
        bool is_case_sensitive;
    };

    struct search {
        bool is_regex;
        bool is_case_sensitive;
        bool is_reverse;
        bool wrap_around;
    };

    struct tabs {
        std::string root_tab_name;
    };

    struct colors {

    };

    struct icons {

    };

    struct ssh_connections {

    };

    struct file_processing_flows {

    };

    struct flag_templates {

    };
}

class config_file_manager
{
public:
    config_file_manager(QString initial_file);

    int get_int(field_selector q) const;
    bool get_bool(field_selector q) const;
    QString get_string(field_selector q) const;

    config::grep grep;
    config::search search;
    config::tabs tabs;
    config::colors colors;
    config::icons icons;
    config::ssh_connections ssh_connections;
    config::file_processing_flows file_processing_flows;
    config::flag_templates flag_templates;

private:
    chaiscript::ChaiScript engine;

    void load_chai_config(QString filename);
    void setup_config_chai_env();
};

#endif // CONFIG_FILE_MANAGER_H
