/***************************************************************************
File		: GPSSensorValidator.cpp
Project		: AdvBoard
Description	: Class for validating a gps sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/GPSSensorValidator.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QObject>

bool GPSSensorValidator::validate(const QJsonObject &sensor, const QJsonObject &boundaries)
{
    const QJsonValue minValue = boundaries["min"];
    const QJsonValue maxValue = boundaries["max"];

    const QJsonValue& min = sensor["min"];
    const QJsonValue& max = sensor["max"];

    const QJsonObject& gpsPosMin = min.toObject();
    const QJsonObject& gpsPosMax = max.toObject();

    const QJsonObject& gpsPosLimitMin = minValue.toObject();
    const QJsonObject& gpsPosLimitMax = maxValue.toObject();

    const double latMin = gpsPosMin["lat"].toDouble();
    const double latMax = gpsPosMax["lat"].toDouble();
    const double latLimitMin = gpsPosLimitMin["lat"].toDouble();
    const double latLimitMax = gpsPosLimitMax["lat"].toDouble();

    if (latMin > latMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "GPS sensor [lat] range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if (latMin < latLimitMin || latMin >= latLimitMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString ="GPS sensor [lat] range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if (latMax <= latLimitMin || latMax > latLimitMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "GPS sensor [lat] range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    const double lonMin = gpsPosMin["lon"].toDouble();
    const double lonMax = gpsPosMax["lon"].toDouble();
    const double lonLimitMin = gpsPosLimitMin["lon"].toDouble();
    const double lonLimitMax = gpsPosLimitMax["lon"].toDouble();

    if (lonMin > lonMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "GPS sensor [lon] range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    if (lonMin < lonLimitMin || lonMin >= lonLimitMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "GPS sensor [lon] range out of range, ID: "+
                           QString::number(id);
        return false;
    }

    if (lonMax <= lonLimitMin || lonMax > lonLimitMax)
    {
        const int id = sensor["id"].toInt();
        m_errorString = "GPS sensor [lon] range out of range, ID: "+
                           QString::number(id);
        return false;
    }
    return true;
}
