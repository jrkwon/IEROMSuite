#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QBuffer>
#include <iostream>

#include "SliceAreaDetectorController.h"
#include "SliceAreaDetector.h"
#include "Settings.h"
#include "Metadata.h"
#include "Mission.h"

ierom::QPoint loadFromSharedMemory()
{
    if (!sharedMemory.attach()) {
        std::cout << "Unable to attach to shared memory segment." << std::endl;
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    ierom::QPoint sliceAreaPosition;

    sharedMemory.lock();
    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> sliceAreaPosition.x;
    in >> sliceAreaPosition.y;

    sharedMemory.unlock();

    sharedMemory.detach();
    ui.label->setPixmap(QPixmap::fromImage(image));

    return sliceAreaPosition;
}

//////////////////////////////////////////////////////////////////////////////
/// \brief main
/// \param argc
/// \param argv[1]: a column number where DetectorController takes care of
/// \return
///
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();

    ierom::settings::Settings settings;
    ierom::Metadata metadata;
    ierom::Mission mission;

    if(args.size() < 2) {
        std::cout << ">>> IEROM Slice Area Dectector Controller "
                  << settings.processInfo.detector.version.major << "."
                  << settings.processInfo.detector.version.minor
                  << " <<<" << std::endl;
        std::cout << "Detects the slice areas of all IEROM raw images in a column." << std::endl;

        QFileInfo pathInfo(args[0]);
        QString fileName(pathInfo.completeBaseName());
        std::cout << qPrintable(fileName )<< " ColumnNumber" << std::endl;
        return false;
    }

    ierom::DetectorController detectorController;
    QString columnNumStr = args[1];
    detectorController.columnNumber = columnNumStr.toInt();

    // create the destination directory name using ID name from Metatdata
    detectorController.destinationDirectory
            = QString("%1/%2/").arg(mission.processedImageDirectory).arg(metadata.tissueSample.id);
    if(!QDir(detectorController.destinationDirectory).exists())
        QDir().mkdir(detectorController.destinationDirectory);

    //////////////////
    /// Detector full file path
    QString detectorProcessName = QString("%1/%2%3%4/%5%6")
                                    .arg(settings.suiteDir)
                                    .arg(settings.processInfo.pathPrefix)
                                    .arg(settings.processInfo.detector.name)
                                    .arg(settings.processInfo.partialPath)
                                    .arg(settings.processInfo.detector.name)
                                    .arg(settings.processInfo.processExt);

    qDebug() << detectorProcessName;

    /////////////////
    // Column folder name - padding 0s
    QString formatStr = "%0" + QString("%1d").arg(settings.processInfo.detector.columNumberDigits);
    QString formattedColumnNumber;
    formattedColumnNumber.sprintf(formatStr.toStdString().c_str(), detectorController.columnNumber);

    /////////////////
    // Template file path
    QString templateFilePath = QString("%1%2%3")
            .arg(detectorController.destinationDirectory)
            .arg(settings.processInfo.detector.templateFileName)
            .arg(metadata.imageFileExtension);

    //qDebug() << templateFilePath;

    /////////////////
    // Make a list of all images in a specified column number
    QString rawImagePathWithColumnNumber
            = QString("%1/%2").arg(mission.rawImageDirectory).arg(formattedColumnNumber);
    QDir rawImageDir(rawImagePathWithColumnNumber);
    QStringList filters;
    filters << QString("*%1").arg(metadata.imageFileExtension);
    rawImageDir.setNameFilters(filters);
    QStringList imageFileList = rawImageDir.entryList(QDir::Files);
    QString imageFileName;

    std::cout << ">>> IEROM Slice Area Dectector Controller ver 1.0 <<<" << std::endl;
    std::cout << "Inovokes a Detector to detect a slice area in a raw image" << std::endl;
    std::cout << "and does the same thing in a column for all images." << std::endl;
    std::cout << "Src: " << qPrintable(mission.rawImageDirectory) << std::endl;
    std::cout << "Dst: " << qPrintable(detectorController.destinationDirectory) << std::endl;
    std::cout << "Col: " << qPrintable(formattedColumnNumber) << std::endl;
    std::cout << "# of files: " << imageFileList.count() << std::endl;

    ierom::QPoint sliceAreaPosition;
    for (int i = 0; i < imageFileList.count(); i++) {
        imageFileName = QString("%1/%2")
                            .arg(rawImagePathWithColumnNumber)
                            .arg(imageFileList[i]);

        QStringList detectorArgs;
        detectorArgs << imageFileName
                     << QString::number(metadata.sectioning.sliceSize.width)
                     << templateFilePath << settings.processInfo.globalSharedMemoryKey << "-v";

        detectorController.process.start(detectorProcessName, detectorArgs);
        detectorController.process.waitForFinished();

        if(detectorController.isProcessError)
            break;

        sliceAreaPosition = loadFromSharedMemory();
        std::cout << i+1 << "/" << imageFileList.count() << ": " << qPrintable(imageFileList[i])
                  << ": x = " << sliceAreaPosition.x
                  << ": y = " << sliceAreaPosition.y << std::endl;

    }


    return true; //a.exec();
}
