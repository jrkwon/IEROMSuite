#include "SliceAreaPositionWriter.h"

#include <QFile>
#include <QTextStream>
#include <QVectorIterator>

IEROM_NAMESPACE_START

SliceAreaPositionWriter::SliceAreaPositionWriter(QString fileName)
{
    this->fileName = fileName;
//    this->numberOfSlicesFromExistingFile = 0;

    SliceAreaInfo sliceAreaInfo;
    QFile file(this->fileName);
    if(file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        in.readLine(); // first line - header
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList items = line.split('\t');
            if(items.size() < 3)
                break;
            sliceAreaInfo.fileName = items[0];
            sliceAreaInfo.sliceArea.setX(items[1].toInt());
            sliceAreaInfo.sliceArea.setY(items[2].toInt());
            this->sliceAreas.append(sliceAreaInfo);
//            this->numberOfSlicesFromExistingFile++;
        }
        file.close();
    }
}

bool SliceAreaPositionWriter::write()
{
    QFile file(this->fileName);
    QTextStream out(&file);

    if(!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Error: Cannot write file "
                     << qPrintable(fileName) << ": "
                     << qPrintable(file.errorString()) << "\n";
            return false;
        }
        out << "name" << "\t" << "startx" << "\t" << "starty" << "\n";
    }
    else {
        if(!file.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Error: Cannot open file for appending "
                     << qPrintable(fileName) << ": "
                     << qPrintable(file.errorString()) << "\n";
            return false;
        }
    }

    SliceAreaInfo lastItem = sliceAreas.last();

    out << lastItem.fileName << "\t"
        << lastItem.sliceArea.x() << "\t"
        << lastItem.sliceArea.y() << "\n";

//    for (int i = 0; i < sliceAreas.size(); i++) {
//        out << sliceAreas[i].fileName << "\t"
//            << sliceAreas[i].sliceArea.x() << "\t"
//            << sliceAreas[i].sliceArea.y() << "\n";
//    }

    file.close();
    return true;
}

IEROM_NAMESPACE_END
