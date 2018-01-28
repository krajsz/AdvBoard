/***************************************************************************
File		: AdvSensorItem.h
Project		: AdvBoard
Description	: Sensor graphics item
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/view/AdvSensorItem.h"
#include "src/sensors/TemperatureSensor.h"
#include "src/sensors/HumiditySensor.h"

#include <QPainter>
#include <QDebug>

AdvSensorItem::AdvSensorItem(AbstractSensor::SensorType type, const int id, QGraphicsItem *parent) : QObject(),  QGraphicsItem(parent)
{
    switch (type) {
    case AbstractSensor::SensorType::TemperatureSensor:
        m_sensor = new TemperatureSensor(id);
        break;
    case AbstractSensor::SensorType::AccelerationSensor:

        break;
    case AbstractSensor::SensorType::GPSpositionSensor:

        break;
    case AbstractSensor::SensorType::HumiditySensor:
        m_sensor = new HumiditySensor(id);
        break;
    default:
        break;
    }

    connect(this, &AdvSensorItem::updateSensor, m_sensor, &AbstractSensor::update);
}

AbstractSensor* AdvSensorItem::sensor()
{
    return m_sensor;
}

QRectF AdvSensorItem::boundingRect() const
{
    return QRectF();
}

void AdvSensorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (m_sensor->type()) {
    case AbstractSensor::SensorType::AccelerationSensor:

        break;
    case AbstractSensor::SensorType::GPSpositionSensor:

        break;
    case AbstractSensor::SensorType::HumiditySensor:
        painter->drawText(10, 10, m_sensor->value().toString() + "%");

        break;
    case AbstractSensor::SensorType::TemperatureSensor:
        painter->drawText(10, 10, m_sensor->value().toString()+ "C");
        break;
    default:
        break;
    }
}
