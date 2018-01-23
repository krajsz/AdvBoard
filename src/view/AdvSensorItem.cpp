#include "AdvSensorItem.h"

AdvSensorItem::AdvSensorItem(QGraphicsObject *parent) : QObject(parent)
{
    connect(m_sensor, &AbstractSensor::dataChanged, this, &AdvSensorItem::updateSensor);
}
