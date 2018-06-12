#include "src/VideoRecorder.h"
#include <QSize>
#include <QImage>

VideoRecorder::VideoRecorder(QObject *parent) : QObject(parent)
{
}

bool VideoRecorder::open(const QString &fileName, int fourcc, double fps, const QSize &frameSize)
{
	cv::Size size {frameSize.width(), frameSize.height()};
	return m_videoWriter.open(fileName.toStdString(), fourcc, fps, size);
}

void VideoRecorder::stop()
{
	m_videoWriter.release();
}

void VideoRecorder::writeFrame(const QImage &src)
{
	if (m_videoWriter.isOpened())
	{
		cv::Mat fframe{src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine()};
		cv::Mat result;
		cv::cvtColor(fframe, result, CV_RGB2BGR);
		m_videoWriter << fframe;
	}
}
