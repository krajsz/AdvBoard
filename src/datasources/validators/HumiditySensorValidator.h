/***************************************************************************
File		: HumiditySensorValidator.h
Project		: AdvBoard
Description	: Class for validating a humidity sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef HUMIDITYSENSORVALIDATOR_H
#define HUMIDITYSENSORVALIDATOR_H
#include "src/datasources/validators/SensorValidator.h"

#include <QObject>

class HumiditySensorValidator : public SensorValidator
{

public:
    HumiditySensorValidator() = default;
    bool validate(const QJsonObject& sensor, const QJsonObject &boundaries);
};

#endif // HUMIDITYSENSORVALIDATOR_H
