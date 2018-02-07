/***************************************************************************
File		: TemperatureSensorValidator.cpp
Project		: AdvBoard
Description	: Class for validating a temperature sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/TemperatureSensorValidator.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

bool TemperatureSensorValidator::validate(const QJsonObject &sensor, const QJsonObject& boundaries)
{
    const QJsonValue minValue = boundaries["min"];
    const QJsonValue maxValue = boundaries["max"];

    const QJsonValue& min = sensor["min"];
    const QJsonValue& max = sensor["max"];

    const double tempMin = min.toDouble();
    const double tempMax = max.toDouble();

    const int tempLimitMin = minValue.toDouble();
    const int tempLimitMax = maxValue.toDouble();

    if (tempMin > tempMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Temperature sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if ((tempMin < tempLimitMin) || (tempMin >= tempLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Temperature sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if ((tempMax > tempLimitMax) || (tempMax <= tempLimitMin))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Temperature sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    return true;
}
