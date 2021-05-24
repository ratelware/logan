#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "ui/project_controller.h"

void validate_project_setup(QFile& file) {

}

void make_project_file(QDir& root) {


}

void make_logs_archive(QDir& root) {
    root.mkdir("logs_archive");
}

void make_diagnostics_dir(QDir& root) {
    root.mkdir("diagnostics");
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

}


void set_up_new_project(QDir& dir) {
    make_project_file(dir);
    make_logs_archive(dir);
    make_diagnostics_dir(dir);
    make_local_database(dir);
    make_local_config(dir);
}

project_controller::project_controller()
{

}

void project_controller::set_up(QString path) {
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
        QStringList projectFiles = dir.entryList(QStringList("*.logan"));
        if(projectFiles.isEmpty()) {
            set_up_new_project(dir);
        } else if(projectFiles.size() > 1) {
            throw std::runtime_error("Cannot read workspace - too many project files");
        } else {
            QFile f = QFile(projectFiles[0]);
            validate_project_setup(f);
        }
    } else {
        QFile f = QFile(path);
        validate_project_setup(f);
    }

}
