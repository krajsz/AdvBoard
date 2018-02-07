/***************************************************************************
File		: SensorTypeValidator.cpp
Project		: AdvBoard
Description	: Class for validating a sensor type
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/SensorTypeValidator.h"
#include <QString>

bool SensorTypeValidator::validate(const int type)
{
    const AbstractSensor::SensorType stype = static_cast<AbstractSensor::SensorType>(type);
    switch (stype)
    {
    case AbstractSensor::SensorType::AccelerationSensor:
        break;
    case AbstractSensor::SensorType::SpeedSensor:
        break;
    case AbstractSensor::SensorType::GPSpositionSensor:
        break;
    case AbstractSensor::SensorType::HumiditySensor:
        break;
    case AbstractSensor::SensorType::TemperatureSensor:
        break;
    default:
        m_errorString = "Sensor type invalid, unknown type: " + QString::number(type);
        return false;
    }
    return true;
}

QString SensorTypeValidator::errorString() const
{
    return m_errorString;
}
