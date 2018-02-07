/***************************************************************************
File		: HumiditySensorValidator.cpp
Project		: AdvBoard
Description	: Class for validating a humidity sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/HumiditySensorValidator.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

bool HumiditySensorValidator::validate(const QJsonObject &sensor, const QJsonObject &boundaries)
{
    const QJsonValue minValue = boundaries["min"];
    const QJsonValue maxValue = boundaries["max"];

    const QJsonValue& min = sensor["min"];
    const QJsonValue& max = sensor["max"];

    const double humidityMin = min.toDouble();
    const double humidityMax = max.toDouble();

    const int humidityLimitMin = minValue.toDouble();
    const int humidityLimitMax = maxValue.toDouble();

    if (humidityMin > humidityMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Humidity sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if ((humidityMin < humidityLimitMin) || (humidityMin >= humidityLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Humidity sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if ((humidityMax > humidityLimitMax) || (humidityMax <= humidityLimitMin))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Humidity sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    return true;
}
