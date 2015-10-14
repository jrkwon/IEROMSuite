#include <QCoreApplication>
#include "RawData.h"

//////////////////////////////////////////////////////////////////////////////
/// \brief main This is only for testing RawData class.
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ierom::settings::Settings settings;
    settings.loadSettings();

    QString rawDataJsonFileName = settings.processInfo.detector.rawDataJsonFileName;
    ierom::RawData rawData("K:/KESM Data/2008-01-23 Whole mouse brain vasculature", rawDataJsonFileName);
    rawData.loadRawData();

    return a.exec();
}
