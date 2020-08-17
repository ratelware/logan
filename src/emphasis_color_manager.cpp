#include "emphasis_color_manager.h"

std::unique_ptr<emphasis_color_manager> emphasis_color_manager::instance;

emphasis_color_manager::emphasis_color_manager()
{}

emphasis_color_manager& emphasis_color_manager::get_instance() {
    if(instance == nullptr) {
        instance.reset(new emphasis_color_manager());
    }

    return *instance;
}

QColor emphasis_color_manager::get_next_color(void* display) {
    auto color = used_colors.find(display);
    if(color == used_colors.end()) {
        color = used_colors.insert(std::make_pair(display, 0)).first;
    }

    if(color->second >= colors.size()) {
        generate_new_colors(color->second);
    }

    return colors[color->second++];
}

void emphasis_color_manager::generate_new_colors(std::size_t min_amount) {
    while(colors.size() <= min_amount) {
        colors.push_back(generate_background_color());
    }
}

QColor emphasis_color_manager::generate_background_color() {
    int hue = rand() % 360;
    int saturation = rand() % 100 + 50;
    int light = rand() % 60 + 160;
    return QColor::fromHsl(hue, saturation, light);
}

void emphasis_color_manager::set_initial_colors(const std::vector<QColor>& colors) {
    for(auto c: colors) {
        this->colors.push_back(c);
    }
}
