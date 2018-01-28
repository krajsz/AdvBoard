/***************************************************************************
File		: AbstractSensor.h
Project		: AdvBoard
Description	: Base class for sensors
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include <QJsonObject>
#include <QVariant>

class AbstractSensor : public QObject
{
    Q_OBJECT
public:
    enum SensorType {
        Abstract = 0,
        TemperatureSensor,
        AccelerationSensor,
        HumiditySensor,
        GPSpositionSensor,
        SpeedSensor
    };
    explicit AbstractSensor(const int id, const QVariant& val = QVariant(), SensorType type = Abstract, QObject *parent = nullptr);
    SensorType type() const;
    bool operator==(const AbstractSensor &other) const;
    QVariant value() const;
signals:
    void sensorUpdated();
public slots:
    void update(const QVariant& newvalue);
private:
    SensorType m_type;
    QJsonObject m_sensorData;
    QVariant m_value;
    const int m_id;
};

#endif // ABSTRACTSENSOR_H
