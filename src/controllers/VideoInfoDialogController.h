/***************************************************************************
File		: VideoInfoDialogController.h
Project		: AdvBoard
Description	: Controller class for VideoInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef VIDEOINFODIALOGCONTROLLER_H
#define VIDEOINFODIALOGCONTROLLER_H

#include <QObject>

class VideoInfoDialogController : public QObject
{
    Q_OBJECT
public:
    explicit VideoInfoDialogController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VIDEOINFODIALOGCONTROLLER_H
