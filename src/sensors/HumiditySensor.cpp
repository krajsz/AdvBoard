/***************************************************************************
File		: HumiditySensor.cpp
Project		: AdvBoard
Description	: Humidity sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/HumiditySensor.h"

HumiditySensor::HumiditySensor(const int id, const double humidity, QObject *parent) :
    AbstractSensor(id, humidity, AbstractSensor::SensorType::HumiditySensor, parent)
{
}
