/***************************************************************************
File		: VideoInfoDialogController.h
Project		: AdvBoard
Description	: Controller class for VideoInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef VIDEOINFODIALOGCONTROLLER_H
#define VIDEOINFODIALOGCONTROLLER_H
#include "src/widgets/VideoLoadingDialog.h"

#include <QObject>

class VideoInfoDialogController : public QObject
{
    Q_OBJECT
public:
    explicit VideoInfoDialogController(QObject *parent = nullptr);
    void setView(VideoLoadingDialog* const view);
    VideoLoadingDialog* const view() const;
signals:

public slots:
private:
    VideoLoadingDialog* m_view;
};

#endif // VIDEOINFODIALOGCONTROLLER_H
