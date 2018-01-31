/***************************************************************************
File		: GPSpositionSensor.cpp
Project		: AdvBoard
Description	: GPS position sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/GPSpositionSensor.h"

GPSpositionSensor::GPSpositionSensor(const int id, const QPointF &pos, QObject *parent) :
    AbstractSensor(id, QPointF(0,0), QPointF{90, 90}, pos, AbstractSensor::GPSpositionSensor, parent)
{
}
