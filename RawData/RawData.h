#ifndef RAWDATA_H
#define RAWDATA_H

#include <QDebug>
#include <QString>
#include <QDate>
#include <QJsonObject>

#include "Settings.h"

IEROM_NAMESPACE_START

#define kRawDataJsonFileName "RawData.json"

struct StartEndDate
{
    QString start;
    QString end;
};

struct Size
{
    int width;
    int depth;
    int height;
};

class TissueSample
{
public:
    void read(const QJsonObject &json);

public:
    QString id;
    QString specimen;
    QString organ;
    QString stain;
    QString object;
    QString sectioningPlane;
    QString scope;
    StartEndDate startEndDate;
    Size size;
};

struct VoxelResol
{
    double width;
    double depth;
    double height;
};

struct SliceSize
{
    int width;
    int height;
};

struct Columns
{
    int start;
    int end;
};

struct RangeZ
{
    double minZ;
    double maxZ;
};

class Sectioning
{
public:
    void read(const QJsonObject &json);

public:
    QString knifeEdge;
    VoxelResol voxelResol;
    SliceSize sliceSize;
    Columns columns;
    RangeZ rangeZ;
};

class RawData
{
public:
    RawData(QString basePath, QString rawDataJsonFileName);

    bool loadRawData();
    void read(const QJsonObject &json);

public:
    QString basePath; // where the RawData.json is
    QString rawDataJsonFileName;
    TissueSample tissueSample;
    Sectioning sectioning;
};

IEROM_NAMESPACE_END

#endif // RAWDATA_H
