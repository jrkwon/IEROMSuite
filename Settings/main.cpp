#include <QCoreApplication>
#include "Settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ierom::settings::Settings settings;
    settings.loadSettings();

    return a.exec();
}
