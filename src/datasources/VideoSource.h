/***************************************************************************
File		: VideoSource.h
Project		: AdvBoard
Description	: MotorcycleDashboard dashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QGraphicsVideoItem>
#include <QUrl>
#include <QMediaPlayer>

class QSize;
class VideoSource : public QGraphicsVideoItem
{
    Q_OBJECT
public:

    explicit VideoSource(QGraphicsVideoItem *parent = nullptr);
    QUrl path() const;
    void resize(const QSize& size);
signals:
    void videoLoaded();
    void loadPercent(int percent);
public slots:
    void loadP(int percent);
    void play();
    void setVideo(const QUrl& url);
    void positionChanged(qint64 position);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
private:
    QUrl m_path;
    QMediaPlayer* m_player;
};

#endif // VIDEOSOURCE_H
