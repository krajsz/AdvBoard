/***************************************************************************
File		: AbstractDashboard.cpp
Project		: AdvBoard
Description	: Base class of the dashboards
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/dashboards/AbstractDashboard.h"

#include <QGraphicsObject>
#include <QPropertyAnimation>

#include <QDebug>

#define DASHBOARD_SENSORITEMS_PADDING 15

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

QRectF AbstractDashboard::boundingRect() const
{
    QRectF brect;
    brect.setLeft(0);
    brect.setTop(0);
    int width = 0;
    int maxHeight = 0;

    for (const AdvSensorItem* const item : sensorItems())
    {
        width += item->boundingRect().width() + DASHBOARD_SENSORITEMS_PADDING;
        if (item->boundingRect().height() > maxHeight)
            maxHeight = item->boundingRect().height();
    }

    brect.setWidth(width);
    brect.setHeight(maxHeight + DASHBOARD_SENSORITEMS_PADDING);
    return brect;
}

void AbstractDashboard::updateSensors(const QVector<QVariant>& values)
{
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

void AbstractDashboard::initSensors(const QVector<QJsonObject> &sensorInfoData, const int animationInterval)
{
    for (int i = 0; i < sensorInfoData.size(); ++i)
    {
        QJsonObject sensorData = sensorInfoData.at(i);
        const int type = sensorData["type"].toInt();
        const int id = sensorData["id"].toInt();

        AdvSensorItem* sensor = new AdvSensorItem(static_cast<AbstractSensor::SensorType>(type), id, this);
        connect(sensor->sensor(), &AbstractSensor::valueChanged, this, [=](){ emit sensorsUpdated();});
        sensor->sensor()->animation()->setDuration(animationInterval);

        m_advSensorItems.push_back(sensor);
    }
    emit sensorsInitialised();
}
