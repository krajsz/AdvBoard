#ifndef VIDEORECORDER_H
#define VIDEORECORDER_H

#include <QObject>
#include <QSize>

#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class VideoRecorder : public QObject
{
    Q_OBJECT
public:
	struct VideoWriterConstructData {
		VideoWriterConstructData() : fileName(QLatin1String()), fourcc(-1), fps(0), size(QSize(-1, -1))
		{
		}
		QString fileName;
		int fourcc;
		double fps;
		QSize size;

		VideoWriterConstructData& operator =(const VideoWriterConstructData& other)
		{
			fileName = other.fileName;
			fourcc = other.fourcc;
			fps = other.fps;
			size = other.size;

			return *this;
		}
	};

    explicit VideoRecorder(QObject *parent = nullptr);

	bool open(const VideoWriterConstructData& data);

signals:

public slots:
	void writeFrame(const QImage& frame);

	void stop();
private:
	cv::VideoWriter m_videoWriter;

};

#endif // VIDEORECORDER_H
