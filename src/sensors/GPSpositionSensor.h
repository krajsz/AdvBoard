/***************************************************************************
File		: SpeedSensor.h
Project		: AdvBoard
Description	: Speed sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef GPSPOSITIONSENSOR_H
#define GPSPOSITIONSENSOR_H

#include "src/sensors/AbstractSensor.h"
#include <QObject>
#include <QPointF>

class GPSpositionSensor : public AbstractSensor
{
    Q_OBJECT
public:
    explicit GPSpositionSensor(const int id, const QPointF& pos = QPointF(), QObject* parent = nullptr);
private:

};

#endif // GPSPOSITIONSENSOR_H
