/***************************************************************************
File		: AdvVideoScene.cpp
Project		: AdvBoard
Description	: Represents the view's scene
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/

#include "src/view/AdvVideoScene.h"
#include "src/dashboards/MotorcycleDashboard.h"

AdvVideoScene::AdvVideoScene(QGraphicsScene *parent) : QGraphicsScene(parent),
    m_video(new VideoSource),
    m_dashBoard(nullptr)
{
}

void AdvVideoScene::setup()
{
    addItem(m_video);
    addItem(m_dashBoard);
    setSceneRect(0, 0, m_video->boundingRect().width(), m_video->boundingRect().height());

    emit sceneSetupDone();
}

void AdvVideoScene::sensorsUpdated()
{
    update();
}

void AdvVideoScene::initDashboard(int type)
{
    AbstractDashboard::DashboardType ttype = static_cast<AbstractDashboard::DashboardType>(type);

    switch (ttype) {
    case AbstractDashboard::DashboardType::MotorcycleDashboard:
        m_dashBoard = new MotorcycleDashboard;
        break;
    case AbstractDashboard::DashboardType::HikerDashboard:

        break;
    case AbstractDashboard::DashboardType::BikerDashboard:

        break;
    default:
        break;
    }

    connect(this, &AdvVideoScene::initSensorSignal, m_dashBoard, &AbstractDashboard::initSensors);
    connect(this, &AdvVideoScene::updateSensorsSignal, m_dashBoard, &AbstractDashboard::updateSensors);
    connect(m_dashBoard, &AbstractDashboard::sensorsInitialised, this, &AdvVideoScene::setup);
    connect(m_dashBoard, &AbstractDashboard::sensorsUpdated, this, &AdvVideoScene::sensorsUpdated);
}

AbstractDashboard* AdvVideoScene::dashboard()
{
    return m_dashBoard;
}

VideoSource* AdvVideoScene::video()
{
    return m_video;
}
