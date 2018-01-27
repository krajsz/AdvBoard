/***************************************************************************
File		: TemperatureSensor.cpp
Project		: AdvBoard
Description	: Temperature sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const int id, const double temp, QObject *parent) :
    AbstractSensor(id, temp, AbstractSensor::TemperatureSensor, parent)
{
}
