/***************************************************************************
File		: AccelerationSensor.cpp
Project		: AdvBoard
Description	: Acceleration sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/AccelerationSensor.h"
#include <QDebug>

AccelerationSensor::AccelerationSensor(const int id, const QPointF& minAccel, const QPointF& maxAccel, const QPointF &acceleration, QObject *parent) :
    AbstractSensor(id, minAccel, maxAccel,
                   acceleration, AbstractSensor::AccelerationSensor, parent)
{
    setDrawingPosition(AbstractSensor::Overlap);
}

double AccelerationSensor::xMinAcceleration() const
{
	return minValue().toPointF().x();
}

double AccelerationSensor::xMaxAcceleration() const
{
	return maxValue().toPointF().x();
}

double AccelerationSensor::yMinAcceleration() const
{
	return minValue().toPointF().y();
}

double AccelerationSensor::yMaxAcceleration() const
{
	return maxValue().toPointF().y();
}
