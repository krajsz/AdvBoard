/***************************************************************************
File		: AdvMainController.cpp
Project		: AdvBoard
Description	: Main controller class
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "AdvMainController.h"

AdvMainController::AdvMainController(QObject* parent) : QObject(parent),
    m_sensorDataInfoDialogController(nullptr),
    m_sensorDataValidatingDialogController(nullptr),
    m_videoInfoDialogController(nullptr),
    m_settingDialogController(nullptr),
    m_sensorDataReader(new SensorDataReader),
    m_viewController(new AdvViewController)
{
    connect(m_sensorDataReader, &SensorDataReader::initDashBoard, m_viewController, &AdvViewController::initDashboard);
    connect(m_sensorDataReader, &SensorDataReader::initSensors, m_viewController, &AdvViewController::initSensors);
    connect(m_sensorDataReader, &SensorDataReader::dataRead, m_viewController, &AdvViewController::dataRead);
}
AdvMainController::~AdvMainController()
{
    if (m_sensorDataInfoDialogController)
    {
        delete m_sensorDataInfoDialogController;
    }
    if (m_sensorDataValidatingDialogController)
    {
        delete m_sensorDataValidatingDialogController;
    }
    if (m_settingDialogController)
    {
        delete m_settingDialogController;
    }
    if (m_videoInfoDialogController)
    {
        delete m_videoInfoDialogController;
    }

    delete m_viewController;
}

void AdvMainController::openSensorData(const QString &dataFile)
{
    m_sensorDataReader->setFile(dataFile);
    m_sensorDataReader->read(true);

    connect(m_sensorDataReader, &SensorDataReader::dataInvalid, this, &AdvMainController::sensorDataInvalid);
}

void AdvMainController::start(const AdvMainController::Mode mode, bool live)
{
    switch (mode)
    {
    case AdvMainController::GuiMode:
        m_sensorDataInfoDialogController = new SensorDataInfoDialogController;
        m_sensorDataValidatingDialogController = new SensorDataValidatingDialogController;
        m_videoInfoDialogController= new VideoInfoDialogController;
        m_settingDialogController = new SettingDialogController;
        break;
    case AdvMainController::SilentMode:
        break;
    default:
        break;
    }

    Q_UNUSED(live)
}

AdvViewController* AdvMainController::viewController()
{
    return m_viewController;
}

SensorDataInfoDialogController* AdvMainController::sensorDataInfoDialogController()
{
    return m_sensorDataInfoDialogController;
}

SensorDataValidatingDialogController* AdvMainController::sensorDataValidatingDialogController()
{
    return m_sensorDataValidatingDialogController;
}

SettingDialogController* AdvMainController::settingDialogController()
{
    return m_settingDialogController;
}

VideoInfoDialogController* AdvMainController::videoInfoDialogController()
{
    return m_videoInfoDialogController;
}

SensorDataReader* AdvMainController::sensorDataReader()
{
    return m_sensorDataReader;
}


