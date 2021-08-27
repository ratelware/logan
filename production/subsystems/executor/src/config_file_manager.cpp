#include <executor/config_file_manager.h>

#include <QFile>

const int UNUSED = 0;
const QString defaultConfig = ":/presets/configuration.xml";

config_file_manager::config_file_manager(QString initial_file)
{
    load_chai_config(initial_file);
}

void config_file_manager::load_chai_config(QString filename) {
    setup_config_chai_env();
    engine.eval(QFile(filename).readAll().toStdString());
}

void config_file_manager::setup_config_chai_env() {
    engine.add(chaiscript::user_type<config::grep>(), "grep_config_t");
    engine.add(chaiscript::user_type<config::search>(), "search_config_t");
    engine.add(chaiscript::user_type<config::tabs>(), "tabs_config_t");
    engine.add(chaiscript::user_type<config::colors>(), "colors_config_t");
    engine.add(chaiscript::user_type<config::icons>(), "icons_config_t");
    engine.add(chaiscript::user_type<config::ssh_connections>(), "ssh_connections_config_t");
    engine.add(chaiscript::user_type<config::file_processing_flows>(), "file_processing_flows_config_t");
    engine.add(chaiscript::user_type<config::flag_templates>(), "flag_templates_config_t");

    engine.add(chaiscript::var(std::ref(grep)), "grep_config");
    engine.add(chaiscript::var(std::ref(search)), "search_config");
    engine.add(chaiscript::var(std::ref(tabs)), "tabs_config");
    engine.add(chaiscript::var(std::ref(colors)), "colors_config");
    engine.add(chaiscript::var(std::ref(icons)), "icons_config");
    engine.add(chaiscript::var(std::ref(ssh_connections)), "ssh_connections_config");
    engine.add(chaiscript::var(std::ref(file_processing_flows)), "file_processing_flows_config");
    engine.add(chaiscript::var(std::ref(flag_templates)), "flag_templates_config");
}
