#include "DetectorController.h"
#include <iostream>

IEROM_NAMESPACE_START

DetectorController::DetectorController()
{
    isProcessError = isFinished = false;
    //startX = -1;

    connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(updateErrorOutput()));
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateOutput()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));

}

void DetectorController::updateErrorOutput()
{
    QByteArray errorArray = process.readAllStandardError();
    std::cerr << qPrintable(QString::fromLocal8Bit(errorArray));
}

void DetectorController::updateOutput()
{
    QByteArray errorArray = process.readAllStandardError();
    std::cout << qPrintable(QString::fromLocal8Bit(errorArray));
}

void DetectorController::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitStatus == QProcess::CrashExit)
    {
        qDebug() << "Detector crashes.";
        isProcessError = true;
    }

    qDebug() << "exitCode is " << exitCode << ".";
//    else {
//        switch(exitCode) {
//        case -1:
//            qDebug() << "Detection failed.";
//            break;
//        case 0:
//            qDebug() << "Error occurred.";
//            break;
//        default:
//            ////qDebug() << "Detection succeeded.";
//            //startX = exitCode;
//        }
//    }
    isFinished = true;
}

void DetectorController::processError(QProcess::ProcessError error)
{
    if(error == QProcess::FailedToStart)
    {
        qDebug() << "Detector not found.";
    }
    isProcessError = isFinished = true;
}

IEROM_NAMESPACE_END
