#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <executor/project_controller.h>
#include <executor/project_workspace.h>

const char* PROJECT_FILE_NAME = "project.logan";
const char* CONFIG_FILE_NAME = "config.json";
const char* LOG_ARCHIVE_DIR = "logs_archive";
const char* DIAGNOSTICS_DIR = "diagnostics";

std::shared_ptr<project_workspace> project_controller::validate_project_setup(QFile& file) {
    QFileInfo fi = QFileInfo(file);
    workspace = std::make_shared<project_workspace>(fi.absoluteFilePath());
    return workspace;
}

void make_project_file(QDir& root) {
    QString config_file = root.absoluteFilePath(PROJECT_FILE_NAME);
    QFile file(config_file);

    file.open(QFile::WriteOnly | QFile::Truncate);
    file.write("HELLO");
    file.close();
}

void make_logs_archive(QDir& root) {
    root.mkdir(LOG_ARCHIVE_DIR);
}

void make_diagnostics_dir(QDir& root) {
    root.mkdir(DIAGNOSTICS_DIR);
}

void prepare_database_schema(QSqlDatabase& db) {
    QSqlQuery query(db);
    query.exec(
"create table greps();"
"create table searches();"
"create table files();"
""
""
                );
}

void make_local_database(QDir& root) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(root.absoluteFilePath("local_database.sqlite"));
    db.open();
    prepare_database_schema(db);
}

void make_local_config(QDir& root) {
    QString config_file = root.absoluteFilePath("config.json");
    QFile file(config_file);

    file.open(QFile::WriteOnly | QFile::Truncate);
    file.write("HELLO");
    file.close();
}


std::shared_ptr<project_workspace> project_controller::set_up_new_project(QDir& dir) {
    make_project_file(dir);
    make_logs_archive(dir);
    make_diagnostics_dir(dir);
    make_local_database(dir);
    make_local_config(dir);

    workspace = std::make_shared<project_workspace>(dir.absoluteFilePath(PROJECT_FILE_NAME));
    return workspace;
}

project_controller::project_controller()
{

}

std::shared_ptr<project_workspace> project_controller::set_up(QString path) {
    QFileInfo d = QFileInfo(path);

    if(!d.exists()) {
        QDir dir = QDir(path);
        bool created = dir.mkpath(path);
        if(!created) {
            throw std::runtime_error("Cannot create workspace");
        }
    }

    d.refresh();

    if(d.isDir()) {
        QDir dir = QDir(path);
        if(!dir.exists()) {
            throw std::runtime_error("Workspace directory does not exist");
        }

        QFile projectFile = dir.absoluteFilePath(PROJECT_FILE_NAME);
        if(!projectFile.exists()) {
            return set_up_new_project(dir);
        } else {
            return validate_project_setup(projectFile);
        }
    } else {
        QFile f = QFile(path);
        return validate_project_setup(f);
    }

}
