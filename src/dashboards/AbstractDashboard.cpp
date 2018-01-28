/***************************************************************************
File		: AbstractDashboard.cpp
Project		: AdvBoard
Description	: Base class of the dashboards
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/dashboards/AbstractDashboard.h"

#include <QGraphicsObject>
#include <QDebug>

AbstractDashboard::AbstractDashboard(const DashboardType dashboardType, QGraphicsObject *parent) : QGraphicsObject(parent),
    m_type(dashboardType)
{
}

AbstractDashboard::DashboardType AbstractDashboard::dashboardType() const
{
    return m_type;
}

QVector<AdvSensorItem*> AbstractDashboard::sensorItems() const
{
    return m_advSensorItems;
}

int AbstractDashboard::numberOfSensors() const
{
    return m_advSensorItems.size();
}

void AbstractDashboard::updateSensors(const QVector<QVariant>& values)
{
    qDebug() << "update sensors" << values.size();
    qDebug() << "advsensorItems" << m_advSensorItems.size();

    Q_ASSERT(values.size() == m_advSensorItems.size());

    for (int i = 0; i < m_advSensorItems.size(); ++i)
    {
        emit m_advSensorItems[i]->updateSensor(values[i]);
    }
    emit sensorsUpdated();
}

void AbstractDashboard::layoutSensors()
{
}

void AbstractDashboard::initSensors(const QVector<QJsonObject> &sensorInfoData)
{
    for (int i = 0; i < sensorInfoData.size(); ++i)
    {
        QJsonObject sensorData = sensorInfoData.at(i);
        const int type = sensorData["type"].toInt();
        const int id = sensorData["id"].toInt();

        AdvSensorItem* sensor = new AdvSensorItem(static_cast<AbstractSensor::SensorType>(type), id, this);
        m_advSensorItems.push_back(sensor);
    }

    layoutSensors();
    qDebug() << "m_advSensorItems " << m_advSensorItems.size();

    qDebug() << "sensorsinitialised" << sensorInfoData.size();
    emit sensorsInitialised();
}
