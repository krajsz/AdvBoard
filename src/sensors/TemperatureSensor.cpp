/***************************************************************************
File		: TemperatureSensor.cpp
Project		: AdvBoard
Description	: Temperature sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const int id, const double minTemp, const double maxTemp,
                                     const double coldWeatherWarningTemperature,
                                     const double temp, QObject *parent) :
    AbstractSensor(id, minTemp, maxTemp, temp, AbstractSensor::TemperatureSensor, parent),
    m_coldWeatherWarningTemperature(coldWeatherWarningTemperature)
{
}

const double TemperatureSensor::coldWeatherWarningTemperature() const
{
    return m_coldWeatherWarningTemperature;
}
