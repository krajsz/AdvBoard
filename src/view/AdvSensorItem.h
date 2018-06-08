#ifndef ADVSENSORITEM_H
#define ADVSENSORITEM_H

#include <QGraphicsObject>
#include "src/sensors/AbstractSensor.h"

class AdvSensorItem final : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit AdvSensorItem(AbstractSensor::SensorType type, const int id, QGraphicsItem *parent = nullptr,
                           const QVariant& maxValue = QVariant(), const QVariant& minValue = QVariant()
                           );
    AbstractSensor* sensor() const;
    virtual QRectF boundingRect() const final override;

signals:
    void updateSensor(const QVariant& newVal);
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final override;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) final override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) final override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) final override;
public slots:

private:
    AbstractSensor* m_sensor;
};

#endif // ADVSENSORITEM_H
