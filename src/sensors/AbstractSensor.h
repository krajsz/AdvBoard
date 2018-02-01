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
#include <QPropertyAnimation>
#include <QPointF>

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

    enum DrawingPosition
    {
        Separate = 0,
        Overlap
    };

    virtual ~AbstractSensor();
    QVariantAnimation* animation();
    explicit AbstractSensor(const int id, const QVariant& minValue, const QVariant& maxValue, const QVariant& val = QVariant(), SensorType type = Abstract, QObject *parent = nullptr);
    SensorType type() const;
    bool operator==(const AbstractSensor &other) const;

    QVariant value() const;
    QVariant minValue() const;
    QVariant maxValue() const;
    void setValue(const QVariant& newValue);

    int id() const;

    void setDrawingPosition(const DrawingPosition position);
    DrawingPosition drawingPosition() const;

signals:
    void sensorUpdated();

public slots:
    void update(const QVariant& newvalue);

private:
    SensorType m_type;
    QJsonObject m_sensorData;
    QVariant m_value;

    QPointF m_test;

    DrawingPosition m_drawingPosition;

    const QVariant m_minValue;
    const QVariant m_maxValue;

    QVariantAnimation* m_animation;
    const int m_id;
};

#endif // ABSTRACTSENSOR_H
