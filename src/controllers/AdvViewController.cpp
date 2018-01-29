/***************************************************************************
File		: AdvViewController.cpp
Project		: AdvBoard
Description	: Controller class of the graphics view
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "AdvViewController.h"

AdvViewController::AdvViewController(QObject *parent) : QObject(parent)
{
}

void AdvViewController::initDashboard(int dashboardType)
{
    emit initDashboardSignal(dashboardType);
}

void AdvViewController::initSensors(const QVector<QJsonObject> &sensordata, const int animationInterval)
{
    emit initSensorsSignal(sensordata, animationInterval);
}

void AdvViewController::dataRead(const QVector<QVariant> &data)
{
    emit dataReadSignal(data);
    emit update();
}
