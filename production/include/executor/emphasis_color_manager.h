#ifndef EMPHASIS_COLOR_MANAGER_H
#define EMPHASIS_COLOR_MANAGER_H

#include <memory>
#include <map>

#include <QColor>

class emphasis_color_manager
{
public:
    static emphasis_color_manager& get_instance();

    QColor get_next_color(void* display);

    void set_initial_colors(const std::vector<QColor>& colors);
private:
    emphasis_color_manager();
    void generate_new_colors(std::size_t min_amount);
    QColor generate_background_color();

    typedef std::size_t color_index_t;
    static std::unique_ptr<emphasis_color_manager> instance;
    std::map<void*, std::size_t> used_colors;
    std::vector<QColor> colors;
};

#endif // EMPHASIS_COLOR_MANAGER_H
