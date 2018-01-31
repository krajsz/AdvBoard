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
#include <QPropertyAnimation>

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
        brect.setWidth(160);
        brect.setHeight(160);
        break;
    case AbstractSensor::SensorType::TemperatureSensor:
        brect.setWidth(165);
        brect.setHeight(140);
        break;
    case AbstractSensor::SensorType::HumiditySensor:
        brect.setWidth(180);
        brect.setHeight(180);
        break;
    case AbstractSensor::SensorType::GPSpositionSensor:
        break;
    case AbstractSensor::SensorType::SpeedSensor:
        brect.setWidth(240);
        brect.setHeight(200);
        break;
    default:
        break;
    }
    return brect;
}

void AdvSensorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (m_sensor->type() == AbstractSensor::SensorType::AccelerationSensor)
    {
        QPen acceleroCirclePen;
        acceleroCirclePen.setWidth(3);
        acceleroCirclePen.setColor(Qt::darkGray);

        painter->setPen(acceleroCirclePen);

        const QPointF acceleroCenter(80,80);

        for(int i = 1; i < 5; ++i)
        {
            painter->drawEllipse(acceleroCenter, i*20, i * 20);
        }
    }

    if (m_sensor->type() == AbstractSensor::SensorType::GPSpositionSensor)
    {
    }


    if (m_sensor->type() == AbstractSensor::SensorType::SpeedSensor)
    {
        const QPointF speedoCenter(100, 40);
        const int speedoRadius = 100;
        QRadialGradient rgrad(speedoCenter, speedoRadius);

        rgrad.setColorAt(0.0, Qt::darkBlue);
        rgrad.setColorAt(0.375, Qt::blue);
        rgrad.setColorAt(0.750, Qt::darkCyan);
        rgrad.setColorAt(1.0, Qt::cyan);

        painter->setBrush(rgrad);
        painter->setOpacity(0.6);

        painter->drawEllipse(speedoCenter, speedoRadius, speedoRadius);

        QBrush pointBrush(Qt::darkBlue);
        painter->setBrush(pointBrush);
        painter->drawEllipse(speedoCenter, 6, 6);

        QFont kmhFont;
        kmhFont.setBold(true);
        kmhFont.setPointSize(12);
        painter->setFont(kmhFont);
        painter->drawText(speedoCenter.x() - 27, speedoCenter.y() + 40, "Km/h");
        QPen kmhPen;
        //50, 109, 255
        kmhPen.setColor(QColor::fromRgb(13,17,18));

        QPainterPath textPath;
        kmhPen.setCapStyle(Qt::RoundCap);
        kmhPen.setWidth(3);
        kmhFont.setPointSize(20);
        textPath.addText(speedoCenter.x() - 10, speedoCenter.y() + 75,
                         kmhFont, QString::number(m_sensor->value().toInt()));

        painter->setPen(kmhPen);
        painter->fillPath(textPath,painter->brush());
        QPen kmhStrokePen;
        kmhStrokePen.setColor(Qt::darkRed);
        kmhStrokePen.setWidth(2);
        painter->strokePath(textPath,kmhStrokePen);

        QConicalGradient speedoGrad;
        speedoGrad.setCenter(speedoCenter);
        speedoGrad.setAngle(270);
        speedoGrad.setColorAt(0.2, Qt::darkRed);
        speedoGrad.setColorAt(0.4, Qt::red);
        speedoGrad.setColorAt(0.7, Qt::darkGreen);
        speedoGrad.setColorAt(0.8, Qt::green);

        QPen speedoLinesPen;
        speedoLinesPen.setBrush(speedoGrad);
        speedoLinesPen.setWidth(22);
        speedoLinesPen.setCapStyle(Qt::RoundCap);

        painter->setPen(speedoLinesPen);
        painter->setOpacity(0.8);
        const int speedoval = m_sensor->value().toInt();
        painter->drawArc(13,-47, speedoRadius * 2 - 25, speedoRadius * 2 - 25,
                         -120 * 16, -speedoval * 16);
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

        QString humidityString = QString::number(m_sensor->value().toDouble(), 'f', 1);
        painter->drawText(10, 60, humidityString + "%");

        if (m_sensor->value().toInt() > 0)
            painter->drawPie(0, 0, 100, 100, 360*16, (m_sensor->value().toInt() * 36* 16)/10);
    }

    if (m_sensor->type() == AbstractSensor::SensorType::TemperatureSensor)
    {
        QFont tempFont;

        tempFont.setPointSize(10);
        tempFont.setCapitalization(QFont::Capitalize);
        tempFont.setItalic(true);
        tempFont.setBold(true);

        painter->setFont(tempFont);
        painter->drawText(0, 0, QLatin1String("Temperature"));

        QBrush tempBrush(QColor(Qt::darkGreen).darker());

        painter->setBrush(tempBrush);
        painter->setOpacity(0.5);

        painter->drawRoundedRect(0, 5, 125, 55, 40, 40);

        tempFont.setItalic(false);

        tempFont.setPointSize(20);
        painter->setFont(tempFont);

        QString temperatureString = QString::number(m_sensor->value().toDouble(),'f', 1);
        painter->drawText(20, 40, temperatureString+ QString::fromUtf8("\u2103"));

        painter->setOpacity(0.8);
        if (m_sensor->value().toDouble() <= 4)
        {
            painter->drawPixmap(125, 10, 40,40, QPixmap(":/pictures/data/coldTempSign.png"));
        }
    }
}
