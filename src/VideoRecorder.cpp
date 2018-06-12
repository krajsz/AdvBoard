#include "src/VideoRecorder.h"

#include <QImage>
#include <QDebug>

VideoRecorder::VideoRecorder(QObject *parent) : QObject(parent)
{
}

bool VideoRecorder::open(const VideoWriterConstructData &data)
{
	cv::Size size (data.size.width(), data.size.height());

	qDebug() << data.fileName << " " << size.width << " " << size.height << " " << data.fourcc << " " << data.fps;
	return m_videoWriter.open(data.fileName.toStdString(), -1, data.fps, size);
}

void VideoRecorder::stop()
{
	m_videoWriter.release();
}

void VideoRecorder::writeFrame(const QImage &src)
{
	if (m_videoWriter.isOpened())
	{
		qDebug() << "saving frame";
		cv::Mat fframe{src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine()};
		cv::Mat result;
		cv::cvtColor(fframe, result, CV_RGB2BGR);
		m_videoWriter << fframe;
	}
	else
	{
		qDebug() << "writer not opened";
	}
}
