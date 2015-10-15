#include <QCoreApplication>
#include "Metadata.h"

//////////////////////////////////////////////////////////////////////////////
/// \brief main This is only for testing Metadata class.
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ierom::settings::Settings settings;
    settings.loadSettings();

    QString metadataJsonFileName = settings.processInfo.detector.metadataJsonFileName;
    ierom::Metadata metadata("K:/KESM Data/2008-01-23 Whole mouse brain vasculature", metadataJsonFileName);
    bool res = metadata.loadMetadata();

    return res; //a.exec();
}
