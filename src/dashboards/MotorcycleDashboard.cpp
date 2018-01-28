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
    /*AdvSensorItem* temperatureGauge = new AdvSensorItem(AbstractSensor::TemperatureSensor, this);
    AdvSensorItem* humidityGauge = new AdvSensorItem(AbstractSensor::HumiditySensor, this);

    m_advSensorItems.push_back(temperatureGauge);
    m_advSensorItems.push_back(humidityGauge);

    humidityGauge->moveBy(50,50);

    moveBy(5, 5);*/
}

void MotorcycleDashboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsItem::paint(painter,option,widget);
}

QRectF MotorcycleDashboard::boundingRect() const
{
    return QRectF();
}

void MotorcycleDashboard::layoutSensors()
{
    for(AdvSensorItem* sensorItem : sensorItems())
    {
        const AbstractSensor::SensorType type = sensorItem->sensor()->type();

        switch (type) {
        case AbstractSensor::SensorType::TemperatureSensor:
            sensorItem->moveBy(50, 80);
            break;
        case AbstractSensor::SensorType::HumiditySensor:
            sensorItem->moveBy(50, 50);

            break;
        default:
            break;
        }
    }
}
