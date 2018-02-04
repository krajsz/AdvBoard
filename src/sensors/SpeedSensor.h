/***************************************************************************
File		: SpeedSensor.h
Project		: AdvBoard
Description	: Speed sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SPEEDSENSOR_H
#define SPEEDSENSOR_H

#include "src/sensors/AbstractSensor.h"
#include <QObject>

class SpeedSensor : public AbstractSensor
{
    Q_OBJECT
public:
    explicit SpeedSensor(const int id, const int maxSpeed = 200, const int speed = 0, QObject* parent = nullptr);
private:

};

#endif // SPEEDSENSOR_H
