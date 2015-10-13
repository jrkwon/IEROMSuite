#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDebug>
#include <QString>
#include <QVector>

#define IEROM_NAMESPACE_START namespace ierom {
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
enum YesNo { No = false, Yes = true };
enum Result { Fail = false, Success = true};

#define SETTINGS_NAMESPACE_START namespace settings {
#define SETTINGS_NAMESPACE_END   }

SETTINGS_NAMESPACE_START

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
    QString detected;
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

class SliceAreaDetector : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    QString rawDataInfoJson;
    QString templateFileName;
    quint8 columNumberDigits;
    quint16 rightEdgeWindowSize;
};

class SliceAreaCorrector : public VersionName {
public:
    void read(const QJsonObject &json);

public:
    quint8 imageChuckThreshold;
    quint16 maxRightEdgeDifference;
    quint8 maxConsecutiveWrongImages;
    quint8 defaultFactorForWindowSize;
    quint8 maxOutlierImages;
};

class SliceAreaCropper  : public VersionName {
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

    SliceAreaDetector detector;
    SliceAreaCorrector corrector;
    SliceAreaCropper cropper;
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

SETTINGS_NAMESPACE_END

IEROM_NAMESPACE_END

#endif // SETTINGS_H
