/***************************************************************************
File		: SpeedSensor.cpp
Project		: AdvBoard
Description	: Speed sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/SpeedSensor.h"

SpeedSensor::SpeedSensor(const int id, const int speed, QObject *parent) :
    AbstractSensor(id, speed, AbstractSensor::SpeedSensor, parent)
{
}
