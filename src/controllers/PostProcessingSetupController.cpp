#include "src/controllers/PostProcessingSetupController.h"
#include "src/view/AdvSensorItem.h"

PostProcessingSetupController::PostProcessingSetupController(QObject *parent): QObject(parent),
    m_sensorDataSourceValidator(new SensorDataSourceValidator),
    m_sensorDataReader(new SensorDataReader),
    m_sensorDataLoaded(false),
    m_videoSourceLoaded(false),
    m_keepAspectRatio(true),
	m_sameAsSource(true),
	m_sensorDataInfoDialogController(nullptr)
{
    connect(m_sensorDataReader, &SensorDataReader::sensorDataIsValid, this, &PostProcessingSetupController::sensorDataIsValidSlot);
}

PostProcessingSetupController::~PostProcessingSetupController()
{
    delete m_sensorDataSourceValidator;
}

void PostProcessingSetupController::sensorDataInfoDialog()
{
	sensorDataInfoDialogController()->setView(m_view->sensorDataInfoDialog());
	sensorDataInfoDialogController()->setSensors(m_sensorDataReader->sensorData());
}

void PostProcessingSetupController::sensorDataIsValidSlot(bool valid)
{
    m_sensorDataLoaded = valid;
    emit sensorDataIsValid(valid, m_sensorDataLoaded && m_videoSourceLoaded);
}

void PostProcessingSetupController::setView(PostProcessingSetupWidget * const view)
{
    m_view = view;
    connectView();
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

void PostProcessingSetupController::setPredefinedSize(int size)
{
    const PostProcessingSetupController::PredefinedSize ssize = static_cast<PostProcessingSetupController::PredefinedSize>(size);
    m_predefinedSize = ssize;
    switch (size) {
    case PostProcessingSetupController::PredefinedSize::FHD:
        m_view->setResolution({1920, 1080});
        break;
    case PostProcessingSetupController::PredefinedSize::HD:
        m_view->setResolution({1280, 720});
        break;
    case PostProcessingSetupController::PredefinedSize::VGA:
        m_view->setResolution({640, 480});
        break;
    default:
        break;
    }
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

void PostProcessingSetupController::setFileToSaveName(const QString &name)
{
	m_fileToSaveName = name;
}

QString PostProcessingSetupController::fileToSaveName() const
{
	return m_fileToSaveName;
}

bool PostProcessingSetupController::ready() const
{
    return m_sensorDataLoaded && m_videoSourceLoaded;
}

void PostProcessingSetupController::videoLoaded()
{
    m_videoSourceLoaded = true;

    qDebug() << "loadedvid";

	qDebug() << m_videoSourceLoaded << " " << m_sensorDataLoaded;
    emit videoLoadedSignal(m_videoSourceLoaded && m_sensorDataLoaded);
}

void PostProcessingSetupController::connectView()
{
	connect(m_view, &PostProcessingSetupWidget::sensorDataInfoDialogButtonClickedSignal, this, &PostProcessingSetupController::sensorDataInfoDialog);
    connect(m_view, &PostProcessingSetupWidget::resolutionHeightChangedSignal, this, &PostProcessingSetupController::setResolutionHeight);
    connect(m_view, &PostProcessingSetupWidget::resolutionWidthChangedSignal, this, &PostProcessingSetupController::setResolutionWidth);
    connect(m_view, &PostProcessingSetupWidget::resolutionPredefinedChangedSignal, this, &PostProcessingSetupController::setPredefinedSize);

    connect(m_view, &PostProcessingSetupWidget::loadSensorDataSignal, this, &PostProcessingSetupController::loadSensorData);
    connect(m_view, &PostProcessingSetupWidget::loadVideoSourceSignal, this, &PostProcessingSetupController::loadVideoSource);

    connect(this, &PostProcessingSetupController::videoLoadedSignal, m_view, &PostProcessingSetupWidget::videoLoaded);
    connect(this, &PostProcessingSetupController::sensorDataIsValid, m_view, &PostProcessingSetupWidget::sensorDataIsValid);
}

void PostProcessingSetupController::loadSensorData(const QString& fileName)
{
    m_sensorDataReader->setFile(fileName);
    m_sensorDataReader->read(true);
}

void PostProcessingSetupController::loadVideoSource(const QUrl& fileUrl)
{
    m_videoSource = new VideoSource;
	qDebug() << "loading video";
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
