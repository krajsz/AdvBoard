/***************************************************************************
File		: GPSpositionSensor.cpp
Project		: AdvBoard
Description	: GPS position sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/GPSpositionSensor.h"

GPSpositionSensor::GPSpositionSensor(const int id, const QPointF &pos, QObject *parent) :
    AbstractSensor(id, pos, AbstractSensor::GPSpositionSensor, parent)
{
}
