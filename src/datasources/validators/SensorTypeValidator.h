/***************************************************************************
File		: SensorTypeValidator.h
Project		: AdvBoard
Description	: Class for validating a sensor type
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORTYPEVALIDATOR_H
#define SENSORTYPEVALIDATOR_H

#include "src/sensors/AbstractSensor.h"

class QString;
class SensorTypeValidator
{
public:
    SensorTypeValidator() = default;
    bool validate(const int type);
    QString errorString() const;
private:
    QString m_errorString;

public slots:
};

#endif // SENSORTYPEVALIDATOR_H
