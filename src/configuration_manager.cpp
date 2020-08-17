#include "configuration_manager.h"

std::unique_ptr<configuration_manager> configuration_manager::instance;

configuration_manager::configuration_manager()
{}

const std::vector<QColor>& configuration_manager::get_initial_emphasis_colors() {
    return std::vector<QColor>();
}

QColor configuration_manager::selection_color() {
    return Qt::yellow;
}

std::pair<int, int> configuration_manager::get_emphasis_hue_range() {
    return std::make_pair(0, 360);
}

std::pair<int, int> configuration_manager::get_emphasis_saturation_range() {
    return std::make_pair(100, 150);
}

std::pair<int, int> configuration_manager::get_emphasis_light_range() {
return std::make_pair(180, 255);
}

std::pair<int, int> configuration_manager::get_emphasis_alpha_range() {
    return std::make_pair(255, 255);
}

bool configuration_manager::get_grep_default_is_regex() {
    return true;
}

bool configuration_manager::get_grep_default_is_case_sensitive() {
    return true;
}

bool configuration_manager::get_grep_default_is_inverse() {
    return false;
}

bool configuration_manager::get_search_default_is_regex() {
    return false;
}

bool configuration_manager::get_search_default_is_case_sensitive() {
    return true;
}

bool configuration_manager::get_search_default_is_reverse() {
    return false;
}

bool configuration_manager::get_search_default_wrap_around() {
    return true;
}

QString configuration_manager::get_root_tab_name() {
    return QString("<base>");
}

configuration_manager& configuration_manager::get_instance() {
    if(instance == nullptr) {
        instance.reset(new configuration_manager());
    }

    return *instance;
}
