/***************************************************************************
File		: SensorDataSourceValidator.cpp
Project		: AdvBoard
Description	: Class for sensor data source validation
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/SensorDataSourceValidator.h"
#include "src/dashboards/AbstractDashboard.h"

#include "src/sensors/AbstractSensor.h"
#include "src/sensors/AccelerationSensor.h"
#include "src/sensors/GPSpositionSensor.h"
#include "src/sensors/TemperatureSensor.h"
#include "src/sensors/HumiditySensor.h"
#include "src/sensors/SpeedSensor.h"

#include "src/datasources/validators/AccelerationSensorValidator.h"
#include "src/datasources/validators/GPSSensorValidator.h"
#include "src/datasources/validators/SpeedSensorValidator.h"
#include "src/datasources/validators/HumiditySensorValidator.h"
#include "src/datasources/validators/TemperatureSensorValidator.h"
#include "src/datasources/validators/DashboardTypeValidator.h"
#include "src/datasources/validators/SensorTypeValidator.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

SensorDataSourceValidator::SensorDataSourceValidator(QObject *parent) : QObject(parent)
{
    QJsonParseError err;
    QFile boundariesFile(":/json/data/sensorValueBoundaries.json");
    if (boundariesFile.open(QFile::ReadOnly))
    {
        const QByteArray arr = boundariesFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(arr, &err);

        m_sensorDataBoundaries = doc.array();
    }
    else
    {
        emit validationError("Boundaries file cannot be opened!");
    }
}

bool SensorDataSourceValidator::validateDashboard(const int type) const
{
    DashboardValidator dashboardTypeValidator;
    if (!dashboardTypeValidator.validate(type))
    {
        emit validationError(dashboardTypeValidator.errorString());
        return false;
    }
    return true;
}

bool SensorDataSourceValidator::validateLiveSensorData(const QJsonArray &sensorData, AbstractDashboard* const dashboard) const
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
bool SensorDataSourceValidator::validateSensors(const QVector<QJsonObject> &sensors) const
{
    int sensorIdx = 0;
    QVector<int> sensorIds;
    sensorIds.reserve(sensors.size());

    for(const QJsonObject& sensor : sensors)
    {
        const int type = sensor["type"].toInt();

        SensorTypeValidator sensorTypeValidator;
        if (!sensorTypeValidator.validate(type))
        {
            emit validationError(sensorTypeValidator.errorString() + ", idx: " + QString::number(sensorIdx));
            return false;
        }
        const int id = sensor["id"].toInt();

        if (sensorIds.contains(id))
        {
            emit validationError("Sensor ID multiple times, idx: " + QString::number(sensorIdx));
            return false;
        }

        sensorIds.push_back(id);

        QJsonObject boundaryObj;

        for (const QJsonValue& sensorBoundaryValue : m_sensorDataBoundaries)
        {
            const QJsonObject obj = sensorBoundaryValue.toObject();
            const int objtype = obj["type"].toInt();

            if (objtype == type)
            {
                boundaryObj = obj;
                break;
            }
        }

        if (!boundaryObj.isEmpty())
        {
            const AbstractSensor::SensorType stype = static_cast<AbstractSensor::SensorType>(type);

            if (stype == AbstractSensor::SensorType::AccelerationSensor)
            {
                AccelerationSensorValidator accelerationSensorValidator;
                if (!accelerationSensorValidator.validate(sensor, boundaryObj))
                {
                    emit validationError(accelerationSensorValidator.errorString() + ", idx: " +
                                         QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::SpeedSensor)
            {
                SpeedSensorValidator speedSensorValidator;
                if (!speedSensorValidator.validate(sensor, boundaryObj))
                {
                    emit validationError(speedSensorValidator.errorString() + ", idx: " +
                                         QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::GPSpositionSensor)
            {
                GPSSensorValidator gpsSensorValidator;
                if (!gpsSensorValidator.validate(sensor, boundaryObj))
                {
                    emit validationError(gpsSensorValidator.errorString() + ", idx: " +
                                         QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::HumiditySensor)
            {
                HumiditySensorValidator humiditySensorValidator;
                if (!humiditySensorValidator.validate(sensor, boundaryObj))
                {
                    emit validationError(humiditySensorValidator.errorString() + ", idx: " +
                                         QString::number(sensorIdx));
                    return false;
                }
            }
            else if (stype == AbstractSensor::SensorType::TemperatureSensor)
            {
                TemperatureSensorValidator temperatureSensorValidator;
                if (!temperatureSensorValidator.validate(sensor, boundaryObj))
                {
                    emit validationError(temperatureSensorValidator.errorString() + ", idx: " +
                                         QString::number(sensorIdx));
                    return false;
                }
            }
            else
            {
                emit validationError("Sensor type invalid somehow, idx: " + QString::number(sensorIdx));
                return false;
            }
            ++sensorIdx;
        }
        else
        {
            qDebug() << "bobjnull";
        }

    }
    return true;
}
