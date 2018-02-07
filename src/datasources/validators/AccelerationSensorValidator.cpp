/***************************************************************************
File		: AccelerationSensorValidator.cpp
Project		: AdvBoard
Description	: Class for validating an acceleration sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/AccelerationSensorValidator.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

bool AccelerationSensorValidator::validate(const QJsonObject &sensor, const QJsonObject &boundaries)
{
    const QJsonValue minValue = boundaries["min"];
    const QJsonValue maxValue = boundaries["max"];

    const QJsonValue& min = sensor["min"];
    const QJsonValue& max = sensor["max"];

    const QJsonObject& accvalMin = min.toObject();
    const QJsonObject& accvalMax = max.toObject();

    const QJsonObject& accvalLimitMin = minValue.toObject();
    const QJsonObject& accvalLimitMax = maxValue.toObject();

    const double xMin = accvalMin["x"].toDouble();
    const double xMax = accvalMax["x"].toDouble();
    const double xLimitMin = accvalLimitMin["x"].toDouble();
    const double xLimitMax = accvalLimitMax["x"].toDouble();

    if (xMin > xMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString ="Acceleration sensor [x] range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if ((xMin < xLimitMin) || (xMin >= xLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Acceleration sensor [x] range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if ((xMax <= xLimitMin) || (xMax > xLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Acceleration sensor [x] range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    const double yMin = accvalMin["y"].toDouble();
    const double yMax = accvalMax["y"].toDouble();
    const double yLimitMin = accvalLimitMin["y"].toDouble();
    const double yLimitMax = accvalLimitMax["y"].toDouble();

    if (yMin > yMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Acceleration sensor [y] range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if ((yMin < yLimitMin) || (yMin >= yLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Acceleration sensor [y] range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if ((yMax <= yLimitMin) || (yMax > yLimitMax))
    {
        const int id = sensor["id"].toInt();
        m_errorString = "Acceleration sensor [y] range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    return true;
}
