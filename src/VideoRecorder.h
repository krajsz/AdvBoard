#ifndef VIDEORECORDER_H
#define VIDEORECORDER_H

#include <QObject>
#include <QMediaRecorder>

class VideoRecorder : public QObject
{
    Q_OBJECT
public:
    explicit VideoRecorder(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VIDEORECORDER_H
