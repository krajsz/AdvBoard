/***************************************************************************
File		: BikerDashboard.cpp
Project		: AdvBoard
Description	: Represents a BikerDashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/dashboards/BikerDashboard.h"
#include "src/sensors/TemperatureSensor.h"
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsObject>

BikerDashboard::BikerDashboard() : AbstractDashboard(AbstractDashboard::DashboardType::BikerDashboard)
{
}

void BikerDashboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsItem::paint(painter,option,widget);
    Q_UNUSED(option)
}

void BikerDashboard::layoutSensors()
{
    for(AdvSensorItem* sensorItem : sensorItems())
    {
        const AbstractSensor::SensorType type = sensorItem->sensor()->type();

        switch (type) {
        case AbstractSensor::SensorType::TemperatureSensor:
            sensorItem->setPos(0, boundingRect().height() - 20 );
            break;
        case AbstractSensor::SensorType::HumiditySensor:
            sensorItem->setPos(boundingRect().width()/2, boundingRect().height() - 20 );
            break;
        case AbstractSensor::SensorType::SpeedSensor:
            sensorItem->setPos(boundingRect().width() - boundingRect().width()/3, boundingRect().height() - 60 );
            break;
        case AbstractSensor::SensorType::GPSpositionSensor:
            break;
        case AbstractSensor::SensorType::AccelerationSensor:
            break;
        default:
            break;
        }
    }
}
