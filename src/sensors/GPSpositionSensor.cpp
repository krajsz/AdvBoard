/***************************************************************************
File		: GPSpositionSensor.cpp
Project		: AdvBoard
Description	: GPS position sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/GPSpositionSensor.h"

GPSpositionSensor::GPSpositionSensor(const int id, const QPointF &pos, double altitude, QObject *parent) :
	AbstractSensor(id, QPointF(0,0), QPointF{90, 90}, pos, AbstractSensor::GPSpositionSensor, parent), m_altitude(altitude)
{
}

double GPSpositionSensor::minLatitude() const
{
    return minValue().toPointF().x();
}

double GPSpositionSensor::maxLatitude() const
{
    return maxValue().toPointF().x();
}

double GPSpositionSensor::minLongitude() const
{
    return minValue().toPointF().y();
}

double GPSpositionSensor::maxLongitude() const
{
    return maxValue().toPointF().y();
}

double GPSpositionSensor::altitude() const
{
	return m_altitude;
}
