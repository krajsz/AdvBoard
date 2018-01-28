/***************************************************************************
File		: MotorcycleDashboard.cpp
Project		: AdvBoard
Description	: Represents a MotorcycleDashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/dashboards/MotorcycleDashboard.h"
#include "src/sensors/TemperatureSensor.h"
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsObject>

MotorcycleDashboard::MotorcycleDashboard() : AbstractDashboard(AbstractDashboard::DashboardType::MotorcycleDashboard)
{
}

void MotorcycleDashboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsItem::paint(painter,option,widget);
}

void MotorcycleDashboard::layoutSensors()
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
