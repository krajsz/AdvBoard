/***************************************************************************
File		: TemperatureSensorValidator.h
Project		: AdvBoard
Description	: Class for validating a temperature sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef TEMPERATURESENSORVALIDATOR_H
#define TEMPERATURESENSORVALIDATOR_H
#include "src/datasources/validators/SensorValidator.h"

class TemperatureSensorValidator : public SensorValidator
{

public:
    TemperatureSensorValidator() = default;
    bool validate(const QJsonObject& sensor, const QJsonObject &boundaries);
};

#endif // TEMPERATURESENSORVALIDATOR_H
