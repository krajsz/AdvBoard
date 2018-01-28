/***************************************************************************
File		: AbstractSensor.cpp
Project		: AdvBoard
Description	: Base class for sensors
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/AbstractSensor.h"
#include <QDebug>

AbstractSensor::AbstractSensor(const int id, const QVariant &val, AbstractSensor::SensorType type, QObject *parent) :
    QObject(parent), m_id(id), m_value(val), m_type(type)
{
}

bool AbstractSensor::operator ==(const AbstractSensor& other) const
{
    return (other.m_id == this->m_id) && (other.type() == this->type());
}

void AbstractSensor::update(const QVariant &newvalue)
{
    m_value = newvalue;
    emit sensorUpdated();
}


QVariant AbstractSensor::value() const
{
    return m_value;
}


AbstractSensor::SensorType AbstractSensor::type() const
{
    return m_type;
}


