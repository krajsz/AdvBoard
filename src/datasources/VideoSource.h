#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QVideoProbe>
#include <QVideoFrame>

class QString;
class VideoSource : public QGraphicsVideoItem
{
    Q_OBJECT
public:
    explicit VideoSource(QGraphicsVideoItem *parent = nullptr);
    QString path() const;
    QVideoFrame currentFrame() const;
signals:

public slots:
    void play();

private:
    QString m_path;
    QMediaPlayer* m_player;
    QVideoProbe* m_probe;
};

#endif // VIDEOSOURCE_H
