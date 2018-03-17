#include "src/datasources/VideoSource.h"
#include <QUrl>
#include <QMediaPlayer>
#include <QDebug>

VideoSource::VideoSource(QGraphicsVideoItem *parent) : QGraphicsVideoItem(parent),
    m_player(new QMediaPlayer(this, QMediaPlayer::VideoSurface))
{
    connect(m_player, &QMediaPlayer::positionChanged, this, &VideoSource::positionChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &VideoSource::mediaStatusChanged);
    connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &VideoSource::loadP);
}

QUrl VideoSource::path() const
{
    return m_path;
}

void VideoSource::resize(const QSize &size)
{
    setSize(size);
}

void VideoSource::play()
{
    if (m_player->isVideoAvailable() && m_player->mediaStatus() == QMediaPlayer::LoadedMedia
            && m_player->state() == QMediaPlayer::StoppedState)
        m_player->play();
}

void VideoSource::setVideo(const QUrl &url)
{
    m_path = url;
    m_player->setMedia(url);
    qDebug() << url;
    m_player->setVideoOutput(this);
    setPos(0, 0);
}

void VideoSource::positionChanged(qint64 position)
{
   // qDebug() << "pos" << position;
}

void VideoSource::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia)
    {
        emit videoLoaded();
    }
}

void VideoSource::loadP(int percent)
{
    qDebug() << "loadP" << percent;
    emit loadPercent(percent);
}
