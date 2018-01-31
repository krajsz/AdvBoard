/***************************************************************************
File		: AccelerationSensor.cpp
Project		: AdvBoard
Description	: Acceleration sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/AccelerationSensor.h"

AccelerationSensor::AccelerationSensor(const int id, const double minAccel, const double maxAccel, const QSizeF &acceleration, QObject *parent) :
    AbstractSensor(id, minAccel, maxAccel,
                   acceleration, AbstractSensor::AccelerationSensor, parent)
{
}

double AccelerationSensor::xMinAcceleration() const
{
    return minValue().toDouble();
}

double AccelerationSensor::xMaxAcceleration() const
{
    return maxValue().toDouble();
}

double AccelerationSensor::yMinAcceleration() const
{
    return minValue().toDouble();
}

double AccelerationSensor::yMaxAcceleration() const
{
    return maxValue().toDouble();
}
