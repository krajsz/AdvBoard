#ifndef POSTPROCESSINGSETUPCONTROLLER_H
#define POSTPROCESSINGSETUPCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QSize>

#include "src/datasources/validators/SensorDataSourceValidator.h"
#include "src/datasources/SensorDataReader.h"
#include "src/view/AdvVideoView.h"
#include "src/controllers/SensorDataInfoDialogController.h"
#include "src/controllers/AdvViewController.h"
#include "src/controllers/VideoInfoDialogController.h"

class PostProcessingSetupController : public QObject
{
    Q_OBJECT
public:
    explicit PostProcessingSetupController(QObject* parent = nullptr);
    ~PostProcessingSetupController();
    enum Preview {
        Normal = 0,
        Fullscreen
    };

    enum SaveFormat {
        MP4 = 0,
        AVI,
        H264
    };

    enum PredefinedSizes {
        Custom = 0,
        FHD,
        HD,
        VGA
    };

    void process();
    bool ready() const;

    void setResolutionWidth(const int width);
    void setResolutionHeight(const int height);

    void setSaveFormat(const SaveFormat format);
    void setSameAsSource(bool sameAsSource);

    void setPreview(Preview preview);

    void setResizePercent(const int percent);

    void loadSensorData(const QString& fileName);
    void loadVideoSource(const QString& fileName);
    QVector<QString> validationErrors() const;

    SensorDataInfoDialogController* sensorDataInfoDialogController();
    AdvViewController* viewController();
    SensorDataReader* sensorDataReader();
    VideoInfoDialogController* videoInfoDialogController();

signals:
    void dashboardValid(bool valid = true);
    void sensorDataInvalid(const QString& errorString);


signals:
    void sensorDataIsValid(bool valid);
private:
    AdvViewController* m_viewController;
    SensorDataReader* m_sensorDataReader;
    VideoInfoDialogController* m_videoInfoDialogController;
    SensorDataInfoDialogController* m_sensorDataInfoDialogController;

    SensorDataSourceValidator* m_sensorDataSourceValidator;

    QSize m_resolution;

    bool m_keepAspectRatio;
    bool m_sameAsSource;
    bool m_sensorDataLoaded;
    bool m_videoSourceLoaded;

    int m_resizePercent;

    SaveFormat m_saveFormat;
    Preview m_preview;
};

#endif // POSTPROCESSINGSETUPCONTROLLER_H
