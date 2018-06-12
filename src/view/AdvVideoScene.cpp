/***************************************************************************
File		: AdvVideoScene.cpp
Project		: AdvBoard
Description	: Represents the view's scene
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/

#include "src/view/AdvVideoScene.h"
#include "src/dashboards/MotorcycleDashboard.h"
#include "src/dashboards/HikerDashboard.h"
#include "src/dashboards/BikerDashboard.h"

#include <QPainter>

AdvVideoScene::AdvVideoScene(QGraphicsScene *parent) : QGraphicsScene(parent),
    m_video(new VideoSource),
    m_dashBoard(nullptr)
{
}

void AdvVideoScene::setup()
{
    addItem(m_video);
    addItem(m_dashBoard);

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
        m_dashBoard = new BikerDashboard;
        break;
    case AbstractDashboard::DashboardType::BikerDashboard:
        m_dashBoard = new HikerDashboard;
        break;
    default:
        break;
    }

    qDebug() << "idb";
    connect(m_dashBoard, &AbstractDashboard::sensorsInitialised, this, &AdvVideoScene::setup);
    connect(m_dashBoard, &AbstractDashboard::sensorsUpdated, this, &AdvVideoScene::sensorsUpdated);
    connect(this, &AdvVideoScene::initSensorSignal, m_dashBoard, &AbstractDashboard::initSensors);
    connect(this, &AdvVideoScene::updateSensorsSignal, m_dashBoard, &AbstractDashboard::updateSensors);
    connect(this, &AdvVideoScene::sceneSetupDone, m_dashBoard, &AbstractDashboard::layoutSensors);
}

QImage AdvVideoScene::grabSceneToImage(const QSize &size)
{
	QImage img(sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
	img.fill(Qt::transparent);
	QPainter painter(&img);

	painter.setRenderHint(QPainter::Antialiasing);
	render(&painter);

	return img.scaled(size);
}
void AdvVideoScene::resize(const QSize &size)
{
    m_video->resize(size);
    m_dashBoard->setPos(size.width() - m_dashBoard->boundingRect().width() - 25,
                        size.height() - m_dashBoard->boundingRect().height() *1.1);
}
AbstractDashboard* AdvVideoScene::dashboard()
{
    return m_dashBoard;
}

VideoSource* AdvVideoScene::video()
{
    return m_video;
}
