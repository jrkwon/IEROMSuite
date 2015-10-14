#ifndef DETECTORCONTROLLER_H
#define DETECTORCONTROLLER_H

#include "Settings.h"
#include "Metadata.h"

#include <QObject>
#include <QProcess>

class DetectorController : public QObject
{
    Q_OBJECT
public:
    DetectorController();

public slots:
    void updateOutput();
    void updateErrorOutput();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

public:
    QProcess process;
    bool isFinished;
    bool isProcessError;
};

#endif // DETECTORCONTROLLER_H
