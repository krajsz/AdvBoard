/***************************************************************************
File		: HumiditySensor.h
Project		: AdvBoard
Description	: Humidity sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "src/sensors/AbstractSensor.h"
#include <QObject>

class HumiditySensor : public AbstractSensor
{
    Q_OBJECT
public:
    explicit HumiditySensor(const int id, const double minHumidity = 0, const double maxHumidity = 100,
                            const double humidity = 0, QObject* parent = nullptr);

private:
};
#endif // HUMIDITYSENSOR_H
