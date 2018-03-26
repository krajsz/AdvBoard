#include "VideoInfoDialogController.h"

VideoInfoDialogController::VideoInfoDialogController(QObject *parent) : QObject(parent)
{

}

void VideoInfoDialogController::setView(VideoLoadingDialog * const view)
{
    m_view = view;
}

VideoLoadingDialog * const VideoInfoDialogController::view() const
{
    return m_view;
}
