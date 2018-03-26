#include "PostProcessingSetupController.h"

PostProcessingSetupController::PostProcessingSetupController(QObject *parent): QObject(parent),
    m_sensorDataSourceValidator(new SensorDataSourceValidator),
    m_sensorDataReader(new SensorDataReader),
    m_sensorDataLoaded(false),
    m_videoSourceLoaded(false),
    m_keepAspectRatio(true),
    m_sameAsSource(true)
{
    connect(m_sensorDataReader, &SensorDataReader::sensorDataIsValid, this, &PostProcessingSetupController::sensorDataIsValidSlot);
}

PostProcessingSetupController::~PostProcessingSetupController()
{
    delete m_sensorDataSourceValidator;
}

void PostProcessingSetupController::sensorDataIsValidSlot(bool valid)
{
    m_sensorDataLoaded = valid;
    emit sensorDataIsValid(valid);
}

void PostProcessingSetupController::setView(PostProcessingSetupWidget * const view)
{
    m_view = view;
}

PostProcessingSetupWidget* const PostProcessingSetupController::view() const
{
    return m_view;
}

void PostProcessingSetupController::setResolutionWidth(const int width)
{
    m_resolution.setWidth(width);
}

void PostProcessingSetupController::setResolutionHeight(const int height)
{
    m_resolution.setHeight(height);
}

void PostProcessingSetupController::setResizePercent(const int percent)
{
    m_resizePercent = percent;
}

void PostProcessingSetupController::setSaveFormat(const PostProcessingSetupController::SaveFormat format)
{
    m_saveFormat = format;
}

void PostProcessingSetupController::setSameAsSource(bool sameAsSource)
{
    m_sameAsSource = sameAsSource;
}

void PostProcessingSetupController::setPreview(PostProcessingSetupController::Preview preview)
{
    m_preview = preview;
}

bool PostProcessingSetupController::ready() const
{
    return m_sensorDataLoaded && m_videoSourceLoaded;
}

void PostProcessingSetupController::videoLoaded()
{
    m_videoSourceLoaded = true;

    qDebug() << "loadedvid";

    emit videoLoadedSignal();
}

void PostProcessingSetupController::loadSensorData(const QString& fileName)
{
    m_sensorDataReader->setFile(fileName);
    m_sensorDataReader->read(true);
}

void PostProcessingSetupController::loadVideoSource(const QUrl& fileUrl)
{
    m_videoSource = new VideoSource;
    m_videoSource->setVideo(fileUrl);

    connect(m_videoSource, &VideoSource::videoLoaded, this, &PostProcessingSetupController::videoLoaded);
}

QVector<QString> PostProcessingSetupController::validationErrors() const
{
    return m_sensorDataSourceValidator->validationErrors();
}

SensorDataInfoDialogController* PostProcessingSetupController::sensorDataInfoDialogController()
{
    if (m_sensorDataInfoDialogController == nullptr)
    {
        m_sensorDataInfoDialogController = new SensorDataInfoDialogController;
    }
    return m_sensorDataInfoDialogController;
}

VideoInfoDialogController* PostProcessingSetupController::videoInfoDialogController()
{
    if (m_videoInfoDialogController == nullptr)
    {
        m_videoInfoDialogController = new VideoInfoDialogController;
    }
    return m_videoInfoDialogController;
}

AdvViewController* PostProcessingSetupController::viewController()
{
    if (m_viewController == nullptr)
    {
        m_viewController = new AdvViewController;
    }
    return m_viewController;
}
SensorDataReader* PostProcessingSetupController::sensorDataReader()
{
    if (m_sensorDataReader == nullptr)
    {
        m_sensorDataReader = new SensorDataReader;
    }
    return m_sensorDataReader;
}
