/***************************************************************************
File		: SensorDataValidator.cpp
Project		: AdvBoard
Description	: Class for sensor data validating
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/SensorDataValidator.h"
#include "src/dashboards/AbstractDashboard.h"

#include "src/sensors/AbstractSensor.h"
#include "src/sensors/AccelerationSensor.h"
#include "src/sensors/GPSpositionSensor.h"
#include "src/sensors/TemperatureSensor.h"
#include "src/sensors/HumiditySensor.h"
#include "src/sensors/SpeedSensor.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

SensorDataValidator::SensorDataValidator(QObject *parent) : QObject(parent)
{
    m_sensorDataBoundaries = QJsonDocument::fromJson(":/json/data/sensorValueBoundaries.json").array();
}

bool SensorDataValidator::validateDashboard(const int type) const
{
    const AbstractDashboard::DashboardType dtype = static_cast<AbstractDashboard::DashboardType>(type);
    switch (dtype)
    {
    case AbstractDashboard::DashboardType::MotorcycleDashboard:
        break;
    case AbstractDashboard::DashboardType::BikerDashboard:
        break;
    case AbstractDashboard::DashboardType::HikerDashboard:
        break;
    default:
        emit validationError("Dashboard not valid");
        return false;
    }
    return true;
}

bool SensorDataValidator::validateLiveSensorData(const QJsonArray &sensorData, AbstractDashboard* const dashboard) const
{
    if (sensorData.size() != dashboard->sensorItems().size())
    {
        emit validationError("Sensor data invalid");
        return false;
    }
    QVector<int> ids;
    ids.reserve(sensorData.size());
    int dataidx = 0;

    for (const QJsonValue& data : sensorData)
    {
        if (data.isObject())
        {
            const QJsonObject& dataobj = data.toObject();
            const int id = dataobj["id"].toInt();

            if (ids.contains(id))
            {
                emit validationError("Sensor ID multiple times, idx: " + QString::number(dataidx));
                return false;
            }
            const AbstractSensor* const sensor = dashboard->sensorWithId(id);

            if (sensor == nullptr)
            {
                emit validationError("Sensor ID not existing, idx: " + QString::number(dataidx));
                return false;
            }
            ids.push_back(id);

            const QJsonValue value = dataobj["value"];
            if (value.isArray())
            {
                Q_ASSERT(sensor->value().type() == QVariant::PointF);

                const double xval = value[0].toDouble();
                const double yval = value[1].toDouble();

                if (sensor->type() == AbstractSensor::SensorType::AccelerationSensor)
                {
                    const AccelerationSensor* const accsensor= qobject_cast<const AccelerationSensor* const> (sensor);

                    if ((xval < accsensor->xMinAcceleration()) || (xval > accsensor->xMaxAcceleration()))
                    {
                        emit validationError("Acceleration sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }

                    if ((yval < accsensor->yMinAcceleration()) || (yval > accsensor->yMaxAcceleration()))
                    {
                        emit validationError("Acceleration sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
                else if (sensor->type() == AbstractSensor::SensorType::GPSpositionSensor)
                {
                    const GPSpositionSensor* const gpsposSensor= qobject_cast<const GPSpositionSensor* const> (sensor);

                    if ((xval < gpsposSensor->minLatitude()) || (xval > gpsposSensor->maxLatitude()))
                    {
                        emit validationError("GPS sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }

                    if ((yval < gpsposSensor->minLongitude()) || (yval > gpsposSensor->maxLongitude()))
                    {
                        emit validationError("GPS sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
            }
            else
            {
                if (sensor->type() == AbstractSensor::SensorType::TemperatureSensor)
                {
                    const TemperatureSensor* const temperatureSensor= qobject_cast<const TemperatureSensor* const> (sensor);
                    const double temp = value.toDouble();

                    if ((temp < temperatureSensor->minValue().toDouble()) || (temp > temperatureSensor->maxValue().toDouble()))
                    {
                        emit validationError("Temperature sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
                else if (sensor->type() == AbstractSensor::SensorType::HumiditySensor)
                {
                    const HumiditySensor* const humiditySensor= qobject_cast<const HumiditySensor* const> (sensor);
                    const double humidity = value.toDouble();

                    if ((humidity < humiditySensor->minValue().toDouble()) || (humidity > humiditySensor->maxValue().toDouble()))
                    {
                        emit validationError("Humidity sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
                else if (sensor->type() == AbstractSensor::SensorType::SpeedSensor)
                {
                    const SpeedSensor* const speedSensor= qobject_cast<const SpeedSensor* const> (sensor);
                    const int speed = value.toInt();

                    if ((speed < speedSensor->minValue().toInt()) || (speed > speedSensor->maxValue().toInt()))
                    {
                        emit validationError("Speed sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
            }
            ++dataidx;
        }
    }
    return true;
}
bool SensorDataValidator::validateSensors(const QVector<QJsonObject> &sensors) const
{
    int sensorIdx = 0;
    QVector<int> sensorIds;
    sensorIds.reserve(sensors.size());

    for(const QJsonObject& sensor : sensors)
    {
        const int type = sensor["type"].toInt();
        const AbstractSensor::SensorType stype = static_cast<AbstractSensor::SensorType>(type);
        switch (stype)
        {
        case AbstractSensor::SensorType::AccelerationSensor:
            break;
        case AbstractSensor::SensorType::SpeedSensor:
            break;
        case AbstractSensor::SensorType::GPSpositionSensor:
            break;
        case AbstractSensor::SensorType::HumiditySensor:
            break;
        case AbstractSensor::SensorType::TemperatureSensor:
            break;
        default:
            emit validationError("Sensor type invalid, idx: " + QString::number(sensorIdx));
            return false;
        }
        const int id = sensor["id"].toInt();

        if (sensorIds.contains(id))
        {
            emit validationError("Sensor ID multiple times, idx: " + QString::number(sensorIdx));
            return false;
        }

        sensorIds.push_back(id);

        QJsonValue minValue;
        QJsonValue maxValue;
        for (const QJsonValue& sensorBoundaryValue : m_sensorDataBoundaries)
        {
            const QJsonObject& obj = sensorBoundaryValue.toObject();
            const int objtype = obj["type"].toInt();

            if (objtype == type)
            {
                minValue = obj["min"];
                maxValue = obj["max"];
                break;
            }
        }

        if (!minValue.isNull() && !maxValue.isNull())
        {
            const QJsonValue& min = sensor["min"];
            const QJsonValue& max = sensor["max"];

            if (stype == AbstractSensor::SensorType::AccelerationSensor)
            {
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
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if ((xMin < xLimitMin) || (xMin >= xLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if ((xMax <= xLimitMin) || (xMax > xLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                const double yMin = accvalMin["y"].toDouble();
                const double yMax = accvalMax["y"].toDouble();
                const double yLimitMin = accvalLimitMin["y"].toDouble();
                const double yLimitMax = accvalLimitMax["y"].toDouble();

                if (yMin > yMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if ((yMin < yLimitMin) || (yMin >= yLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if ((yMax <= yLimitMin) || (yMax > yLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

            }
            else if (stype == AbstractSensor::SensorType::SpeedSensor)
            {
                const int speedMin = min.toInt();
                const int speedMax = max.toInt();

                const int speedLimitMin = minValue.toInt();
                const int speedLimitMax = maxValue.toInt();

                qDebug() << speedMin << " " << speedMax << " " << speedLimitMin << " " << speedLimitMax;

                if (speedMin > speedMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if ((speedMin < speedLimitMin) || (speedMin >= speedLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if ((speedMax > speedLimitMax) || (speedMax <= speedLimitMin))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::GPSpositionSensor)
            {
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
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if (latMin < latLimitMin || latMin >= latLimitMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if (latMax <= latLimitMin || latMax > latLimitMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                const double lonMin = gpsPosMin["lon"].toDouble();
                const double lonMax = gpsPosMax["lon"].toDouble();
                const double lonLimitMin = gpsPosLimitMin["lon"].toDouble();
                const double lonLimitMax = gpsPosLimitMax["lon"].toDouble();

                if (lonMin > lonMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if (lonMin < lonLimitMin || lonMin >= lonLimitMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if (lonMax <= lonLimitMin || lonMax > lonLimitMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::HumiditySensor)
            {
                const double humidityMin = min.toDouble();
                const double humidityMax = max.toDouble();

                const int humidityLimitMin = minValue.toDouble();
                const int humidityLimitMax = maxValue.toDouble();

                if (humidityMin > humidityMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if ((humidityMin < humidityLimitMin) || (humidityMin >= humidityLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if ((humidityMax > humidityLimitMax) || (humidityMax <= humidityLimitMin))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::TemperatureSensor)
            {
                const double tempMin = min.toDouble();
                const double tempMax = max.toDouble();

                const int tempLimitMin = minValue.toDouble();
                const int tempLimitMax = maxValue.toDouble();

                if (tempMin > tempMax)
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
                if ((tempMin < tempLimitMin) || (tempMin >= tempLimitMax))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }

                if ((tempMax > tempLimitMax) || (tempMax <= tempLimitMin))
                {
                    emit validationError("Sensor range out of range, idx: " + QString::number(sensorIdx));
                    return false;
                }
            }
            else
            {
                emit validationError("Sensor invalid, idx: " + QString::number(sensorIdx));
                return false;
            }

        }

        ++sensorIdx;
    }
    return true;
}
