#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <memory>
#include <vector>
#include <QColor>

class configuration_manager
{
public:
    const std::vector<QColor>& get_initial_emphasis_colors();
    QColor selection_color();

    std::pair<int, int> get_emphasis_hue_range();
    std::pair<int, int> get_emphasis_saturation_range();
    std::pair<int, int> get_emphasis_light_range();
    std::pair<int, int> get_emphasis_alpha_range();

    bool get_grep_default_is_regex();
    bool get_grep_default_is_case_sensitive();
    bool get_grep_default_is_inverse();

    bool get_search_default_is_regex();
    bool get_search_default_is_case_sensitive();
    bool get_search_default_is_reverse();
    bool get_search_default_wrap_around();

    QString get_root_tab_name();
    QString icon_for_text(QString text);

    static configuration_manager& get_instance();

    const std::vector<QString>& get_favorite_icons_paths();
    std::vector<QString> get_all_icons_paths();

private:
    configuration_manager();

    static std::unique_ptr<configuration_manager> instance;
};

#endif // CONFIGURATION_MANAGER_H
