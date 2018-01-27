#ifndef ADVSENSORITEM_H
#define ADVSENSORITEM_H

#include <QGraphicsObject>
#include "src/sensors/AbstractSensor.h"

class AdvSensorItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit AdvSensorItem(AbstractSensor::SensorType type, QGraphicsObject *parent = nullptr);
    AbstractSensor* sensor();
signals:
    void updateSensor(const QVariant& newVal);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
public slots:

private:
    AbstractSensor* m_sensor;
};

#endif // ADVSENSORITEM_H
