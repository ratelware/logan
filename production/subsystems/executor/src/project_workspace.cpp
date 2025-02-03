#include <executor/project_workspace.h>

#include <utility>

project_workspace::project_workspace(QString path) : path_(std::move(path))
{}
