/***************************************************************************
File		: SensorValidator.h
Project		: AdvBoard
Description	: Base class for validating a sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORVALIDATOR_H
#define SENSORVALIDATOR_H
#include <QString>

class QJsonObject;
class SensorValidator
{
public:
    SensorValidator() = default;
    QString errorString() const;
    virtual bool validate(const QJsonObject& sensor, const QJsonObject &boundaries) = 0;
protected:
    QString m_errorString;
};

#endif // SENSORVALIDATOR_H
