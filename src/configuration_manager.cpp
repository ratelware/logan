#include "configuration_manager.h"

#include <QDir>

std::unique_ptr<configuration_manager> configuration_manager::instance;

configuration_manager::configuration_manager()
{}

const auto colors = std::vector<QColor>();

const std::vector<QColor>& configuration_manager::get_initial_emphasis_colors() {
    return colors;
}

const auto favorites = std::vector<QString>{
       "",
       ":/icons/exclaim.png",
       ":/icons/exclaim-question.png",
       ":/icons/question.png",
       ":/icons/fail.png",
       ":/icons/pass.png",
       ":/icons/lightning.png",
       ":/icons/bug.png"
   };

const std::vector<QString>& configuration_manager::get_favorite_icons_paths() {
    return favorites;
}

std::vector<QString> configuration_manager::get_all_icons_paths() {
    auto dir(QDir(":/icons/"));
    auto entries = dir.entryList();

    auto vec = std::vector<QString>(entries.length());
    std::transform(entries.begin(), entries.end(), vec.begin(), [&dir](QString i) { return QFileInfo(dir, i).canonicalFilePath(); });

    return vec;
}

QString configuration_manager::icon_for_text(QString text) {
    const auto comp = text.toLower();
    if(comp.contains("error")) {
        return ":/icons/fail.png";
    } else if(comp.contains("warn")) {
        return ":/icons/warn.png";
    } else if(comp.contains("info")) {
        return ":/icons/info.png";
    } else if(comp.contains("debug")) {
        return "";
    } else if(comp.contains("trace")) {
        return ":/icons/footprints.png";
    } else if(comp.contains("magic")) {
        return ":/icons/mage.png";
    } else {
        return "";
    }
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
