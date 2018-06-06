/***************************************************************************
File		: AdvViewController.cpp
Project		: AdvBoard
Description	: Controller class of the graphics view
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/controllers/AdvViewController.h"
#include "src/view/AdvVideoView.h"

#include <QDebug>

AdvViewController::AdvViewController(QObject *parent) : QObject(parent)
{
}

void AdvViewController::initDashboard(int dashboardType)
{
	qDebug() << "ids";

    emit initDashboardSignal(dashboardType);
}

void AdvViewController::initSensors(const QVector<QJsonObject> &sensordata, const int animationInterval)
{
    qDebug() << "iss";
    emit initSensorsSignal(sensordata, animationInterval);
}

void AdvViewController::dataRead(const QVector<QJsonValue> &data)
{
    emit dataReadSignal(data);
    emit update();
}

void AdvViewController::setView(AdvVideoView * const view)
{
	qDebug() << "should happen before initsensors signal";

    m_view = view;

	connect(this, &AdvViewController::setVideo, m_view->videoScene()->video(), &VideoSource::setVideo);
	connect(this, &AdvViewController::play, m_view->videoScene()->video(), &VideoSource::play);
	connect(this, &AdvViewController::initDashboardSignal, m_view->videoScene(), &AdvVideoScene::initDashboard);
	connect(this, &AdvViewController::dataReadSignal, m_view->videoScene(), &AdvVideoScene::updateSensorsSignal);
	connect(this, &AdvViewController::initSensorsSignal, m_view->videoScene(), &AdvVideoScene::initSensorSignal);
}

AdvVideoView* const AdvViewController::view() const
{
    return m_view;
}
