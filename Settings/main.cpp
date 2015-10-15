#include <QCoreApplication>
#include "Settings.h"

//////////////////////////////////////////////////////////////////////////////
/// \brief main This is only for testing Settings class.
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ierom::settings::Settings settings;
    bool res = settings.loadSettings();

    return res; //a.exec();
}
