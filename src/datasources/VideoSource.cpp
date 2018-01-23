#include "VideoSource.h"

VideoSource::VideoSource(QGraphicsVideoItem *parent) : QObject(parent), m_player(new QMediaPlayer(this))
{
    m_player->setVideoOutput(this);
}

QString VideoSource::path() const
{
    return m_path;
}

void VideoSource::play()
{
    m_player->play();
}
