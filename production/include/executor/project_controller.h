#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

#include <QFile>
#include <QDir>
#include <memory>

class project_workspace;

class project_controller
{
public:
    project_controller();

    std::shared_ptr<project_workspace> set_up(QString path);
    std::shared_ptr<project_workspace> validate_project_setup(QFile& file);
    std::shared_ptr<project_workspace> set_up_new_project(QDir& dir);

private:
    std::shared_ptr<project_workspace> workspace;
};

#endif // PROJECT_CONTROLLER_H
