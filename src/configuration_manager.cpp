#include "configuration_manager.h"

#include <QDir>
#include <QRegularExpression>

QString qStringFromQDom(QDomElement e) {
    return e.nodeValue();
}

QColor qColorFromQDom(QDomElement e) {
    QString rgb = e.nodeValue();
    return QColor(rgb.mid(1,2).toInt(nullptr, 16), rgb.mid(3,2).toInt(nullptr, 16), rgb.mid(5,2).toInt(nullptr, 16));
}

std::pair<QRegularExpression, QString> qIconMappingFromQDom(QDomElement e) {
    auto regex = e.namedItem("regex");
    auto icon = e.namedItem("icon");

    return std::make_pair(QRegularExpression(regex.nodeValue()), icon.nodeValue());
}

std::unique_ptr<configuration_manager> configuration_manager::instance;

configuration_manager::configuration_manager(QString config) : config_files(config)
{}

const std::vector<QColor> configuration_manager::get_initial_emphasis_colors() {
    return config_files.get_vector_of<QColor>(xml_selector{"colors/initial_emphasis_colors/color"}, qColorFromQDom);
}

std::vector<QString> configuration_manager::get_favorite_icons_paths() {
    return config_files.get_vector_of<QString>(xml_selector{"icons_config/favorites"}, qStringFromQDom);
}

std::vector<QString> configuration_manager::get_all_icons_paths() {
    auto dirs = config_files.get_vector_of<QString>(xml_selector{"icons_config/paths/dir"}, qStringFromQDom);
    auto items = config_files.get_vector_of<QString>(xml_selector{"icons_config/paths/file"}, qStringFromQDom);

    for(auto d: dirs) {
        auto dir = QDir(d);
        auto entries = dir.entryList();
        items.reserve(items.size() + entries.size());
        for(auto e: entries) {
            items.push_back(QFileInfo(dir, e).canonicalFilePath());
        }
    }

    return items;
}

QString configuration_manager::icon_for_text(QString text) {
    auto mappings = config_files.get_vector_of<std::pair<QRegularExpression, QString>>(xml_selector {"icons_config/mappings/mapping"}, qIconMappingFromQDom);
    for(auto m: mappings) {
        if(m.first.match(text).hasMatch()) {
            return m.second;
        }
    }

    return "";
}


QColor configuration_manager::selection_color() {
    return config_files.get_t<QColor>(xml_selector { "colors/selection_color" }, qColorFromQDom);
}

std::pair<int, int> configuration_manager::get_emphasis_hue_range() {
    return std::make_pair(
            config_files.get_int(xml_selector { "colors/generated_colors_config/hue_min" }),
            config_files.get_int(xml_selector { "colors/generated_colors_config/hue_max" })
       );
}

std::pair<int, int> configuration_manager::get_emphasis_saturation_range() {
    return std::make_pair(
                config_files.get_int(xml_selector { "colors/generated_colors_config/saturation_min" }),
                config_files.get_int(xml_selector { "colors/generated_colors_config/saturation_max" })
           );
}

std::pair<int, int> configuration_manager::get_emphasis_light_range() {
    return std::make_pair(
                config_files.get_int(xml_selector { "colors/generated_colors_config/light_min" }),
                config_files.get_int(xml_selector { "colors/generated_colors_config/light_max" })
           );
}

std::pair<int, int> configuration_manager::get_emphasis_alpha_range() {
    return std::make_pair(
                config_files.get_int(xml_selector { "colors/generated_colors_config/alpha_min" }),
                config_files.get_int(xml_selector { "colors/generated_colors_config/alpha_max" })
           );}

bool configuration_manager::get_grep_default_is_regex() {
    return config_files.get_bool(xml_selector {"grep_defaults/is_regex"});
}

bool configuration_manager::get_grep_default_is_case_sensitive() {
    return config_files.get_bool(xml_selector {"grep_defaults/is_case_sensitive"});
}

bool configuration_manager::get_grep_default_is_inverse() {
    return config_files.get_bool(xml_selector {"grep_defaults/is_inverse"});
}

bool configuration_manager::get_search_default_is_regex() {
    return config_files.get_bool(xml_selector {"search_defaults/is_regex"});
}

bool configuration_manager::get_search_default_is_case_sensitive() {
    return config_files.get_bool(xml_selector {"search_defaults/is_case_sensitive"});
}

bool configuration_manager::get_search_default_is_reverse() {
    return config_files.get_bool(xml_selector {"search_defaults/is_reverse"});
}

bool configuration_manager::get_search_default_wrap_around() {
    return config_files.get_bool(xml_selector {"search_defaults/wrap_around"});
}

QString configuration_manager::get_root_tab_name() {
    return config_files.get_string(xml_selector {"tabs_config/root_tab_name"});
}

configuration_manager& configuration_manager::get_instance() {
    if(instance == nullptr) {
        instance.reset(new configuration_manager(""));
    }

    return *instance;
}

configuration_manager& configuration_manager::set_up(QString config) {
    instance.reset(new configuration_manager(config));
    return *instance;
}
