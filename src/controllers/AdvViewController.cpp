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
    m_view = view;
}

AdvVideoView* const AdvViewController::view() const
{
    return m_view;
}
