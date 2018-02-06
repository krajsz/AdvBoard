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

bool SensorDataValidator::validateSensorData(const QVector<QJsonValue> &sensorData, AbstractDashboard* const dashboard) const
{
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
            ids.push_back(id);
            const AbstractSensor* const sensor = dashboard->sensorWithId(id);

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
            dataidx++;
        }
    }
    return true;
}
bool SensorDataValidator::validateSensors(const QVector<QJsonObject> &sensors) const
{

    for(const QJsonObject& sensor : sensors)
    {

    }
    return true;
}
