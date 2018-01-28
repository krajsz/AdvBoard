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
#include "src/controllers/AdvViewController.h"
#include "src/controllers/SensorDataInfoDialogController.h"
#include "src/controllers/SensorDataValidatingDialogController.h"
#include "src/controllers/VideoInfoDialogController.h"
#include "src/controllers/SettingDialogController.h"
#include "src/datasources/LiveSensorDataReader.h"
#include "src/datasources/SensorDataReader.h"

class AdvMainController : public QObject
{
    Q_OBJECT
public:
    explicit AdvMainController(QObject* parent = nullptr);
    ~AdvMainController();
    enum Mode {
        GuiMode = 0,
        SilentMode
    };
    void start(const Mode mode, bool live = false);

    AdvViewController* viewController();
    SensorDataInfoDialogController* sensorDataInfoDialogController();
    SensorDataValidatingDialogController* sensorDataValidatingDialogController();
    VideoInfoDialogController* videoInfoDialogController();
    SettingDialogController* settingDialogController();
    SensorDataReader* sensorDataReader();

private:
    AdvViewController* m_viewController;
    SensorDataInfoDialogController* m_sensorDataInfoDialogController;
    SensorDataValidatingDialogController* m_sensorDataValidatingDialogController;
    SettingDialogController* m_settingDialogController;
    VideoInfoDialogController* m_videoInfoDialogController;
    SensorDataReader* m_sensorDataReader;

signals:
};

#endif // ADVMAINCONTROLLER_H
