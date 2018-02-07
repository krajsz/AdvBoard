/***************************************************************************
File		: SpeedSensorValidator.cpp
Project		: AdvBoard
Description	: Class for validating a speed sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/SpeedSensorValidator.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

bool SpeedSensorValidator::validate(const QJsonObject &sensor, const QJsonObject &boundaries)
{
    const QJsonValue minValue = boundaries["min"];
    const QJsonValue maxValue = boundaries["max"];

    const QJsonValue& min = sensor["min"];
    const QJsonValue& max = sensor["max"];

    const int speedMin = min.toInt();
    const int speedMax = max.toInt();

    const int speedLimitMin = minValue.toInt();
    const int speedLimitMax = maxValue.toInt();

    if (speedMin > speedMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Speed sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if ((speedMin < speedLimitMin) || (speedMin >= speedLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Speed sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if ((speedMax > speedLimitMax) || (speedMax <= speedLimitMin))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Speed sensor range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    return true;
}
