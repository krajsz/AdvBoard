#ifndef VIDEORECORDER_H
#define VIDEORECORDER_H

#include <QObject>

#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class VideoRecorder : public QObject
{
    Q_OBJECT
public:
    explicit VideoRecorder(QObject *parent = nullptr);

	bool open(const QString& fileName,  int fourcc, double fps, const QSize& frameSize);

signals:

public slots:
	void writeFrame(const QImage& frame);

	void stop();
private:
	cv::VideoWriter m_videoWriter;

};

#endif // VIDEORECORDER_H
