#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDebug>
#include <QString>
#include <QVector>

#define IEROM_NAMESPACE_START namespace IEROM {
#define IEROM_NAMESPACE_END   }

IEROM_NAMESPACE_START

#define kDebug                       true

#define kIEROMSuitePathEnv           "IEROM_SUITE_DIR"

#if kDebug
#define kSettingsJsonFileRelPath     "/Settings/Settings.json"
#else
#define kSettingsJsonFileRelPath     "/bin/Settings.json"
#endif
// enums
enum ErrorCode { Error = false, Success = true };
enum YesNo { No = false, Yes = true };

struct Version {
    int major;
    int minor;
};

class SystemInfo
{
public:
    void read(const QJsonObject &json);

public:
    QString author;
    Version version;
    bool debug;
};

class RawImageProp {
public:
    void read(const QJsonObject &json);

public:
    QString sourceImageFileExtension;
    quint8 backgroundColor;
    quint8 minPixelIntensity;
    quint8 maxPixelIntensity;
};

class DirectoryName {
public:
    void read(const QJsonObject &json);

public:
    QString cropped;
    QString normalized;
    QString sticherInfo;
    QString stiched;
    QString titled;
    QString scaled;
    QString rotated;
    QString attenuated;
};

class VersionName {
public:
    Version version;
    QString name;
};

class TissueAreaDetector : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    QString rawDataInfoJson;
    QString templateFileName;
    quint8 columNumberDigits;
    quint16 rightEdgeWindowSize;
};

class TissueAreaCorrector : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    quint8 imageChuckThreshold;
    quint16 maxRightEdgeDifference;
    quint8 maxConsecutiveWrongImages;
    quint8 defaultFactorForWindowSize;
    quint8 maxOutlierImages;
};

class TissueAreaCropper  : public VersionName {
public:
    void read(const QJsonObject &json);

public:
};

class IntensityNormalizer : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    quint8 normalizedMinIntensity;
    quint8 normalizedMaxIntensity;
};

class SliceSticherInfo : public VersionName {
public:
    void read(const QJsonObject &json);

public:
};

class SliceSticher : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    QString infoFileName;
    QString infoFormat;
    QString invertImageFlag;
};

class MultiLayerComposer : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    QString indexedImageFileNameFormat;
    QString zPosFileNameFormat;
    quint8 composerUnitDepth;
};

class ProcessInfo {
public:
    void read(const QJsonObject &json);

public:
    long maxProcessWaitTime;
    QString processExt;
    QString partialPath;
    QString pathPrefix;

    TissueAreaDetector detector;
    TissueAreaCorrector corrector;
    TissueAreaCropper cropper;
    IntensityNormalizer normalizer;
    SliceSticherInfo sticherInfo;
    SliceSticher sticher;
    MultiLayerComposer composer;
};

class Settings
{
public:
    bool loadSettings();

    void read(const QJsonObject &json);

public:
    SystemInfo systemInfo;
    RawImageProp rawImageProp;
    DirectoryName directoryName;
    ProcessInfo processInfo;
};

IEROM_NAMESPACE_END

#endif // SETTINGS_H
