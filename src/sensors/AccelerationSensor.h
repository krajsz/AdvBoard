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
#include <QPointF>

class AccelerationSensor : public AbstractSensor
{
    Q_OBJECT
public:
    explicit AccelerationSensor(const int id, const double minAccel = -2, const double maxAccel = 2, const QPointF& acceleration = QPointF(0.01, 0.01), QObject* parent = nullptr);

    double xMinAcceleration() const;
    double yMinAcceleration() const;
    double xMaxAcceleration() const;
    double yMaxAcceleration() const;
private:

};

#endif // ACCELERATIONSENSOR_H
