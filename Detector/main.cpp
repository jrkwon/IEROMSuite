#include <QCoreApplication>
#include <QFileInfo>
#include "SliceAreaDetector.h"

// ---------------------------------
// argv
// 1. Raw image file name
// 2. Slice area width
// 3. Template file name
// 4. Options
//    s: [silence] no message displayed

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();

    if(args.size() < 4)
    {
        std::cout << ">>> KESM Slice Area Dectector ver 1.0 <<<" << std::endl;
        std::cout << "Detects the slice area of an KESM raw image" << std::endl;
        std::cout << "and saves starting x and y positions" << std::endl;

        QFileInfo pathInfo(args[0]);
        QString fileName(pathInfo.completeBaseName());
        std::cout << qPrintable(fileName) << " ImageFileName SliceWidth TemplateFilename [-v]" << std::endl;
        return -1;
    }
    QString rawImageFileName = args[1];
    int sliceWidth = args[2].toInt();
    QString templateName = args[3];

    ierom::SliceAreaDetector detector(rawImageFileName, sliceWidth, templateName);
    bool isVerbose = false;
    if(args.size() >= 5) {
        isVerbose = (args[4] == "-v") ? false : true;
    }
    detector.setVerbose(isVerbose);
    ierom::Coord sliceStartPosition;
    detector.getSliceAreaPosition(sliceStartPosition);

    return sliceStartPosition.x; //a.exec();
}
