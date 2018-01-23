/***************************************************************************
File		: AdvMainController.h
Project		: AdvBoard
Description	: Main controller class
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ADVMAINCONTROLLER_H
#define ADVMAINCONTROLLER_H

#include <QObject>
#include "AdvViewController.h"
#include "SensorDataInfoDialogController.h"
#include "SensorDataValidatingDialogController.h"
#include "VideoInfoDialogController.h"

#include "src/AdvBoardMain.h"

class AdvMainController : public QObject
{
    Q_OBJECT
public:
    explicit AdvMainController(QObject* parent = nullptr);

private:
    AdvBoardMain* m_mainWindow;
    AdvViewController* m_viewController;
    SensorDataInfoDialogController* m_sensorDataInfoDialogController;
    SensorDataValidatingDialogController* m_sensorDataValidatingDialogController;
    VideoInfoDialogController* m_videoInfoDialogController;

};

#endif // ADVMAINCONTROLLER_H
