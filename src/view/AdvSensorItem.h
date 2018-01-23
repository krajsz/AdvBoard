#ifndef ADVSENSORITEM_H
#define ADVSENSORITEM_H

#include "AbstractSensor.h"

#include <QGraphicsObject>

class AdvSensorItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit AdvSensorItem(QGraphicsObject *parent = nullptr);
signals:

public slots:
private slots:
    void updateSensor();
private:
    AbstractSensor* m_sensor;
};

#endif // ADVSENSORITEM_H
