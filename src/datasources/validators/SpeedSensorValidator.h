/***************************************************************************
File		: SpeedSensorValidator.h
Project		: AdvBoard
Description	: Class for validating a speed sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SPEEDSENSORVALIDATOR_H
#define SPEEDSENSORVALIDATOR_H

#include "src/datasources/validators/SensorValidator.h"

#include <QObject>

class SpeedSensorValidator : public SensorValidator
{
public:
    SpeedSensorValidator() = default;
    bool validate(const QJsonObject& sensor, const QJsonObject &boundaries);
};

#endif // SPEEDSENSORVALIDATOR_H
