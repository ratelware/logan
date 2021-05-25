#include "ui/logan.h"
#include <executor/configuration_manager.h>

#include <QApplication>
#include <QCommandLineParser>

int runLogan(int argc, char *argv[])
{
    QCommandLineParser parser;

    parser.setApplicationDescription("Log analyzer - supporting debugging");
    parser.addHelpOption();
    parser.addVersionOption();

    auto configOption = QCommandLineOption(QStringList() << "c" << "config" << QCoreApplication::translate("main", "Configuration file"));
    configOption.setDefaultValue("");
    parser.addOption(configOption);

    QApplication a(argc, argv);
    a.addLibraryPath(QString(qEnvironmentVariable("SQLDRIVERS_DIR", ".")));

    parser.process(a);

    QString configFile = parser.value(configOption);
    configuration_manager::set_up(configFile);

    Logan w;
    w.show();
    return a.exec();
}
