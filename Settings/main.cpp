#include <QCoreApplication>
#include "Settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IEROM::Settings settings;
    settings.loadSettings();

    return a.exec();
}
