#include "SliceAreaPositionWriter.h"

#include <QFile>
#include <QTextStream>

IEROM_NAMESPACE_START

SliceAreaPositionWriter::SliceAreaPositionWriter(QString fileName)
{
    this->fileName = fileName;
}

bool SliceAreaPositionWriter::write()
{
    QFile file(this->fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot write file "
                 << qPrintable(fileName) << ": "
                 << qPrintable(file.errorString()) << "\n";
        return false;
    }

    QTextStream out(&file);
    out << "name" << "\t" << "startx" << "\t" << "starty" << "\n";

    for (int i = 0; i < sliceAreas.size(); i++) {
        out << sliceAreas[i].fileName << "\t"
            << sliceAreas[i].sliceArea.x() << "\t"
            << sliceAreas[i].sliceArea.y() << "\n";
    }

    file.close();
    return true;
}

IEROM_NAMESPACE_END
