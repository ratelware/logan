#include "logan.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logan w;
    w.show();
    return a.exec();
}
