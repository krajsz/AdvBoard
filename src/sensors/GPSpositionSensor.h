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
	explicit GPSpositionSensor(const int id, const QPointF& pos = QPointF(), double altitude = 0.0, QObject* parent = nullptr);
    double minLatitude() const;
    double maxLatitude() const;
    double minLongitude() const;
    double maxLongitude() const;
	double altitude() const;
private:
	double m_altitude;

};

#endif // GPSPOSITIONSENSOR_H
