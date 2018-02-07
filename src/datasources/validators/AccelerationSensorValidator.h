/***************************************************************************
File		: AccelerationSensorValidator.h
Project		: AdvBoard
Description	: Class for validating an acceleration sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ACCELERATIONSENSORVALIDATOR_H
#define ACCELERATIONSENSORVALIDATOR_H

#include "src/datasources/validators/SensorValidator.h"

class QJsonObject;

class AccelerationSensorValidator: public SensorValidator
{
public:
    AccelerationSensorValidator() = default;
    bool validate(const QJsonObject& sensor, const QJsonObject &boundaries);
};

#endif // ACCELERATIONSENSORVALIDATOR_H
