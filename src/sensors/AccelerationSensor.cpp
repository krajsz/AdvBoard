/***************************************************************************
File		: AccelerationSensor.cpp
Project		: AdvBoard
Description	: Acceleration sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/AccelerationSensor.h"

AccelerationSensor::AccelerationSensor(const int id, const double acceleration, QObject *parent) :
    AbstractSensor(id, acceleration, AbstractSensor::AccelerationSensor, parent)
{
}
