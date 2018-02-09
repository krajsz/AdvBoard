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
        m_validationErrors.push_back("Boundaries file cannot be opened!");
    }
}

bool SensorDataSourceValidator::validateDashboard(const int type)
{
    DashboardValidator dashboardTypeValidator;
    if (!dashboardTypeValidator.validate(type))
    {
        m_validationErrors.push_back(dashboardTypeValidator.errorString());
        return false;
    }
    return true;
}

bool SensorDataSourceValidator::validateLiveSensorData(const QJsonArray &sensorData, AbstractDashboard* const dashboard)
{
    if (sensorData.size() != dashboard->sensorItems().size())
    {
        m_validationErrors.push_back("Sensor data invalid, invalid data count");
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
                m_validationErrors.push_back("Sensor ID multiple times, idx: " + QString::number(dataidx));
                return false;
            }
            const AbstractSensor* const sensor = dashboard->sensorWithId(id);

            if (sensor == nullptr)
            {
                m_validationErrors.push_back("Sensor ID not existing, idx: " + QString::number(dataidx));
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
                        m_validationErrors.push_back("Acceleration sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                    if ((yval < accsensor->yMinAcceleration()) || (yval > accsensor->yMaxAcceleration()))
                    {
                        m_validationErrors.push_back("Acceleration sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
                else if (sensor->type() == AbstractSensor::SensorType::GPSpositionSensor)
                {
                    const GPSpositionSensor* const gpsposSensor= qobject_cast<const GPSpositionSensor* const> (sensor);

                    if ((xval < gpsposSensor->minLatitude()) || (xval > gpsposSensor->maxLatitude()))
                    {
                        m_validationErrors.push_back("GPS sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                    if ((yval < gpsposSensor->minLongitude()) || (yval > gpsposSensor->maxLongitude()))
                    {
                        m_validationErrors.push_back("GPS sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
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
                        m_validationErrors.push_back("Temperature sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
                else if (sensor->type() == AbstractSensor::SensorType::HumiditySensor)
                {
                    const HumiditySensor* const humiditySensor= qobject_cast<const HumiditySensor* const> (sensor);
                    const double humidity = value.toDouble();

                    if ((humidity < humiditySensor->minValue().toDouble()) || (humidity > humiditySensor->maxValue().toDouble()))
                    {
                        m_validationErrors.push_back("Humidity sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
                else if (sensor->type() == AbstractSensor::SensorType::SpeedSensor)
                {
                    const SpeedSensor* const speedSensor= qobject_cast<const SpeedSensor* const> (sensor);
                    const int speed = value.toInt();

                    if ((speed < speedSensor->minValue().toInt()) || (speed > speedSensor->maxValue().toInt()))
                    {
                        m_validationErrors.push_back("Speed sensor data invalid, idx: " + QString::number(dataidx) + value.toString());
                        return false;
                    }
                }
            }
            ++dataidx;
        }
    }
    return true;
}
bool SensorDataSourceValidator::validateSensors(const QVector<QJsonObject> &sensors)
{
    int sensorIdx = 0;
    QVector<int> sensorIds;
    sensorIds.reserve(sensors.size());

    bool valid = true;
    for(const QJsonObject& sensor : sensors)
    {
        const int type = sensor["type"].toInt();

        SensorTypeValidator sensorTypeValidator;
        if (!sensorTypeValidator.validate(type))
        {
            m_validationErrors.push_back(sensorTypeValidator.errorString() + ", idx: " + QString::number(sensorIdx));
            valid = false;
        }
        const int id = sensor["id"].toInt();

        if (sensorIds.contains(id))
        {
            m_validationErrors.push_back("Sensor ID multiple times, idx: " + QString::number(sensorIdx));
            valid = false;
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
                    m_validationErrors.push_back(accelerationSensorValidator.errorString() + ", idx: " +
                                                 QString::number(sensorIdx));
                    valid = false;
                }
            }
            else if (stype == AbstractSensor::SensorType::SpeedSensor)
            {
                SpeedSensorValidator speedSensorValidator;
                if (!speedSensorValidator.validate(sensor, boundaryObj))
                {
                    m_validationErrors.push_back(speedSensorValidator.errorString() + ", idx: " +
                                                 QString::number(sensorIdx));
                    valid = false;
                }
            }
            else if (stype == AbstractSensor::SensorType::GPSpositionSensor)
            {
                GPSSensorValidator gpsSensorValidator;
                if (!gpsSensorValidator.validate(sensor, boundaryObj))
                {
                    m_validationErrors.push_back(gpsSensorValidator.errorString() + ", idx: " +
                                                 QString::number(sensorIdx));
                    valid = false;
                }
            }
            else if (stype == AbstractSensor::SensorType::HumiditySensor)
            {
                HumiditySensorValidator humiditySensorValidator;
                if (!humiditySensorValidator.validate(sensor, boundaryObj))
                {
                    m_validationErrors.push_back(humiditySensorValidator.errorString() + ", idx: " +
                                                 QString::number(sensorIdx));
                    valid = false;
                }
            }
            else if (stype == AbstractSensor::SensorType::TemperatureSensor)
            {
                TemperatureSensorValidator temperatureSensorValidator;
                if (!temperatureSensorValidator.validate(sensor, boundaryObj))
                {
                    m_validationErrors.push_back(temperatureSensorValidator.errorString() + ", idx: " +
                                                 QString::number(sensorIdx));
                    valid = false;
                }
            }
            else
            {
                m_validationErrors.push_back("Sensor type invalid somehow, idx: " + QString::number(sensorIdx));
                valid = false;
            }
            ++sensorIdx;
        }
        else
        {
            qDebug() << "bobjnull";
        }
    }
    return valid;
}

QVector<QString> SensorDataSourceValidator::validationErrors() const
{
    return m_validationErrors;
}
