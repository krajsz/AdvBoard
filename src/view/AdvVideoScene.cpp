/***************************************************************************
File		: AdvVideoScene.cpp
Project		: AdvBoard
Description	: Represents the view's scene
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/

#include "src/view/AdvVideoScene.h"
#include "src/dashboards/MotorcycleDashboard.h"

AdvVideoScene::AdvVideoScene(AbstractDashboard::DashboardType dashboardType, QGraphicsScene *parent) : QGraphicsScene(parent),
    m_video(new VideoSource)
{
    switch (dashboardType) {
    case AbstractDashboard::DashboardType::MotorcycleDashboard:
        m_dashBoard = new MotorcycleDashboard;

        break;
    case AbstractDashboard::DashboardType::BikerDashboard:

        break;
    case AbstractDashboard::DashboardType::HikerDashboard:

        break;
    default:
        break;
    }
}

void AdvVideoScene::setup()
{
    addItem(m_video);
    addItem(m_dashBoard);

    setSceneRect(0, 0, m_video->boundingRect().width(), m_video->boundingRect().height());
}

AbstractDashboard* AdvVideoScene::dashboard()
{
    return m_dashBoard;
}

VideoSource* AdvVideoScene::video()
{
    return m_video;
}
