#ifndef SLICEAREADETECTOR_H
#define SLICEEAREADETECTOR_H

#include <QSharedMemory>
#include "Settings.h"

///////////////////////////
// itk
#include "itkJPEGImageIOFactory.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkImage.h"

const unsigned int g_nDimension = 2;

typedef unsigned char PixelType;
typedef itk::Image<PixelType, g_nDimension> ImageType;
typedef itk::ImageFileReader<ImageType> ReaderType;
typedef itk::ImageFileWriter<ImageType> WriterType;
typedef itk::RegionOfInterestImageFilter< ImageType,
                                          ImageType > FilterType;
typedef itk::ImageLinearConstIteratorWithIndex<ImageType> ConstIteratorType;
typedef itk::ImageLinearIteratorWithIndex<ImageType>      IteratorType;

IEROM_NAMESPACE_START

struct Params
{
    quint8 maxIllumination;
    quint8 minIllumination;
    quint8 maxPixelValue;
};

struct Coord
{
    int x, y;
};

struct SliceRightEdgeTemplate
{
    QString name;
    int width;
    int height;
 };

class SliceAreaDetector
{
public:
    SliceAreaDetector(QString rawFilePath, int sliceWidth, QString templateFilePath, QString sharedMemoryKeyName);

    void setVerbose(bool isVerbose);
    Result getSliceAreaPosition(Coord& coord);

private:
    void reLight(int direction,
                   itk::ImageLinearConstIteratorWithIndex<ImageType> inputIt,
                   itk::ImageLinearIteratorWithIndex<ImageType> outputIt);
    int sumOfAbsoluteDifferences(
            itk::ImageLinearConstIteratorWithIndex<ImageType> searchIt,
            itk::ImageLinearConstIteratorWithIndex<ImageType> templateIt);
    void saveToSharedMemory(Coord sliceAreaPosition);
    void showProgress(int start, int end, int current);
    void displayMessage(QString message);

    ImageType::ConstPointer readFile(QString filePath);

private:
    QString rawFilePath;
    int sliceWidth;
    SliceRightEdgeTemplate sliceRightEdgeTemplate;
    QString sharedMemoryKeyName;
    Coord sliceAreaPosition;
    bool isVerbose;
    Params params;
    QSharedMemory sharedMemory;
};

IEROM_NAMESPACE_END

#endif // SLICEAREADETECTOR_H
