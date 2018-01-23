#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include <QJsonObject>

template<class T>
class AbstractSensor : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSensor(const int id, const T& val, QObject *parent = nullptr);
    SensorType type() const;
    bool operator==(const AbstractSensor<T> &other) const;
    T value() const;
    enum SensorType {
        TemperatureSensor = 0,
        AccelerationSensor,
        HumiditySensor,
        GPSpositionSensor
    };
signals:
    void dataChanged();
public slots:
private:


    SensorType m_type;
    QJsonObject m_sensorData;
    T m_value;
    const int m_id;
};

#endif // ABSTRACTSENSOR_H
