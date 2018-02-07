/***************************************************************************
File		: GPSSensorValidator.h
Project		: AdvBoard
Description	: Class for validating a gps sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef GPSSENSORVALIDATOR_H
#define GPSSENSORVALIDATOR_H
#include "src/datasources/validators/SensorValidator.h"

class GPSSensorValidator : public SensorValidator
{
public:
    GPSSensorValidator() = default;
    bool validate(const QJsonObject& sensor, const QJsonObject &boundaries);
};

#endif // GPSSENSORVALIDATOR_H
