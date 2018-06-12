#include "PreviewController.h"

#include <QDebug>

PreviewController::PreviewController(QObject* parent) : QObject(parent),
	m_view(nullptr),
	m_videoRecorder(nullptr),
	m_writeFrameTimer(nullptr)
{

}

void PreviewController::setView(PreviewWidget * const view)
{
    m_view = view;
}

PreviewController::~PreviewController()
{
	if (m_videoRecorder)
	{
		delete m_videoRecorder;
	}

	if (m_writeFrameTimer)
	{
		delete m_videoRecorder;
	}
}

void PreviewController::setAdvScene(AdvVideoScene * const scene, const VideoRecorder::VideoWriterConstructData &data)
{
	if (m_view)
	{
		m_view->setScene(scene);

		if (m_videoRecorder == nullptr)
		{
			m_videoRecorder = new VideoRecorder;
		}

		if (m_videoRecorder->open(data))
		{
			m_videoRecorderConstructData = data;

			if (!m_writeFrameTimer)
			{
				m_writeFrameTimer = new QTimer(this);
			}
			m_writeFrameTimer->setInterval(1000.0 / m_videoRecorderConstructData.fps);
			connect(m_writeFrameTimer, &QTimer::timeout, this, &PreviewController::sendFrameToWriter);


			m_writeFrameTimer->start();
		}
		else
		{
			qDebug() << "video not opened for write";
		}
	}
}

PreviewWidget* const PreviewController::view() const
{
    return m_view;
}

void PreviewController::sendFrameToWriter()
{
	m_videoRecorder->writeFrame(m_view->advVideoScene()->grabSceneToImage(m_videoRecorderConstructData.size));
}
