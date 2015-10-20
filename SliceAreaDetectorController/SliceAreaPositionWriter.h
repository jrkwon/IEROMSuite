#ifndef SLICEAREAPOSITIONWRITER_H
#define SLICEAREAPOSITIONWRITER_H

#include "Settings.h"
#include <QString>
#include <QPoint>

IEROM_NAMESPACE_START

struct SliceAreaInfo
{
    QString fileName;
    QPoint sliceArea;
    bool valid;
};

class SliceAreaPositionWriter
{
public:
    SliceAreaPositionWriter(QString fileName);

    bool write();

public:
    QVector<SliceAreaInfo> sliceAreas;
    QString fileName;
};

IEROM_NAMESPACE_END

#endif // SLICEAREAPOSITIONWRITER_H
