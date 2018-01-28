/***************************************************************************
File		: AccelerationSensor.h
Project		: AdvBoard
Description	: Acceleration sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ACCELERATIONSENSOR_H
#define ACCELERATIONSENSOR_H

#include "src/sensors/AbstractSensor.h"
#include <QObject>

class AccelerationSensor : public AbstractSensor
{
    Q_OBJECT
public:
    AccelerationSensor(const int id, const double acceleration = 0, QObject* parent = nullptr);
private:

};

#endif // ACCELERATIONSENSOR_H
