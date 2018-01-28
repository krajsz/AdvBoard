/***************************************************************************
File		: AdvSensorItem.h
Project		: AdvBoard
Description	: Sensor graphics item
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/view/AdvSensorItem.h"
#include "src/sensors/TemperatureSensor.h"
#include "src/sensors/HumiditySensor.h"
#include "src/sensors/SpeedSensor.h"
#include "src/sensors/GPSpositionSensor.h"
#include "src/sensors/AccelerationSensor.h"
#include <QPainter>
#include <QDebug>

AdvSensorItem::AdvSensorItem(AbstractSensor::SensorType type, const int id, QGraphicsItem *parent) : QObject(),  QGraphicsItem(parent)
{
    switch (type) {
    case AbstractSensor::SensorType::TemperatureSensor:
        m_sensor = new TemperatureSensor(id);
        break;
    case AbstractSensor::SensorType::AccelerationSensor:
        m_sensor = new AccelerationSensor(id);
        break;
    case AbstractSensor::SensorType::GPSpositionSensor:
        m_sensor = new GPSpositionSensor(id);
        break;
    case AbstractSensor::SensorType::HumiditySensor:
        m_sensor = new HumiditySensor(id);
        break;
    case AbstractSensor::SensorType::SpeedSensor:
        m_sensor = new SpeedSensor(id);
        break;
    default:
        break;
    }

    connect(this, &AdvSensorItem::updateSensor, m_sensor, &AbstractSensor::update);
}

AbstractSensor* AdvSensorItem::sensor()
{
    return m_sensor;
}

QRectF AdvSensorItem::boundingRect() const
{
    QRectF brect;
    brect.setTop(0);
    brect.setLeft(0);
    switch (m_sensor->type()) {
    case AbstractSensor::SensorType::AccelerationSensor:

        break;
    case AbstractSensor::SensorType::TemperatureSensor:
        brect.setWidth(150);
        brect.setHeight(140);
        break;
    case AbstractSensor::SensorType::HumiditySensor:
        brect.setWidth(180);
        brect.setHeight(180);
        break;
    case AbstractSensor::SensorType::GPSpositionSensor:
        break;
    case AbstractSensor::SensorType::SpeedSensor:
        break;
    default:
        break;
    }
    return brect;
}

void AdvSensorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_sensor->type() == AbstractSensor::SensorType::AccelerationSensor)
    {
    }

    if (m_sensor->type() == AbstractSensor::SensorType::GPSpositionSensor)
    {
    }

    if (m_sensor->type() == AbstractSensor::SensorType::SpeedSensor)
    {
    }


    if (m_sensor->type() == AbstractSensor::SensorType::HumiditySensor)
    {
        QFont humidityFont;

        humidityFont.setBold(true);
        humidityFont.setItalic(true);
        humidityFont.setPointSize(10);

        painter->setFont(humidityFont);
        painter->drawText(0, 0, QLatin1String("Humidity"));

        const int blue = (255 * m_sensor->value().toInt())/100;
        QBrush pieBrush(QColor::fromRgb(255 - blue, 0, blue));
        painter->setBrush(pieBrush);
        painter->setOpacity(0.7);

        humidityFont.setPointSize(15);
        humidityFont.setItalic(false);
        painter->setFont(humidityFont);
        painter->drawText(20, 50, m_sensor->value().toString() + "%");

        painter->drawPie(0, 0, 80, 80, 1*16, (m_sensor->value().toInt() * 36* 16)/10);
    }

    if (m_sensor->type() == AbstractSensor::SensorType::TemperatureSensor)
    {
        QFont tempFont;

        painter->setOpacity(0.7);
        tempFont.setPointSize(10);
        tempFont.setCapitalization(QFont::Capitalize);
        tempFont.setItalic(true);
        tempFont.setBold(true);

        painter->setFont(tempFont);
        painter->drawText(0, 0, QLatin1String("Temperature"));

        QBrush tempBrush(QColor(Qt::red));

        painter->setBrush(tempBrush);
        painter->drawRoundRect(0, 0, 125, 55);

        tempFont.setItalic(false);

        tempFont.setPointSize(20);
        painter->setFont(tempFont);
        painter->drawText(20, 40, m_sensor->value().toString()+ QString::fromUtf8("\u2103"));
    }
}
