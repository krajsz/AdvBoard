/***************************************************************************
File		: TemperatureSensor.h
Project		: AdvBoard
Description	: Temperature sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "src/sensors/AbstractSensor.h"
#include <QObject>

class TemperatureSensor : public AbstractSensor
{
    Q_OBJECT
public:
    TemperatureSensor(const int id, const double minTemp = -20, const double maxTemp = 60,
                      const double coldWeatherWarningTemperature = 4, const double temp = 0, QObject* parent = nullptr);
    const double coldWeatherWarningTemperature() const;
private:
    const double m_coldWeatherWarningTemperature;
};

#endif // TEMPERATURESENSOR_H
