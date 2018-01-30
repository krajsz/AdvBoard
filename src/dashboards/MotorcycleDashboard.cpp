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
#include <QPainter>


MotorcycleDashboard::MotorcycleDashboard() : AbstractDashboard(AbstractDashboard::DashboardType::MotorcycleDashboard)
{
}

void MotorcycleDashboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLinearGradient lgrad(this->boundingRect().x(), this->boundingRect().y(),
                          this->boundingRect().x() + this->boundingRect().width(),
                          this->boundingRect().y() + this->boundingRect().height());

    lgrad.setColorAt(0.0, Qt::black);
    lgrad.setColorAt(0.3, Qt::gray);
    lgrad.setColorAt(1.0, Qt::red);

    painter->setOpacity(0.4);
    painter->setBrush(lgrad);

    painter->drawRoundedRect(boundingRect().x() - 10, boundingRect().y(),
                             boundingRect().x() +boundingRect().width() + 10,
                             boundingRect().y()+ boundingRect().height(), 90,90);
}

void MotorcycleDashboard::layoutSensors()
{
    for(AdvSensorItem* sensorItem : sensorItems())
    {
        const AbstractSensor::SensorType type = sensorItem->sensor()->type();

        switch (type) {
        case AbstractSensor::SensorType::TemperatureSensor:
            sensorItem->setPos(0, boundingRect().height() / 2);
            break;
        case AbstractSensor::SensorType::HumiditySensor:
            sensorItem->setPos(boundingRect().width()/2, boundingRect().height()/ 2 );
            break;
        case AbstractSensor::SensorType::SpeedSensor:
            sensorItem->setPos(boundingRect().width() - boundingRect().width()/3, boundingRect().height() /2 - 40 );
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
