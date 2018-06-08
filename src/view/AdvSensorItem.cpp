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

/***************************************************************************/
#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>

AdvSensorItem::AdvSensorItem(AbstractSensor::SensorType type, const int id, QGraphicsItem *parent, const QVariant &maxValue, const QVariant &minValue) : QGraphicsObject(parent)
{
	switch (type) {
	case AbstractSensor::SensorType::TemperatureSensor:
		m_sensor = new TemperatureSensor(id, minValue.toDouble(), maxValue.toDouble());
		break;
	case AbstractSensor::SensorType::AccelerationSensor:
		m_sensor = new AccelerationSensor(id, minValue.toDouble(), maxValue.toDouble());
		break;
	case AbstractSensor::SensorType::GPSpositionSensor:
		m_sensor = new GPSpositionSensor(id);
		break;
	case AbstractSensor::SensorType::HumiditySensor:
		m_sensor = new HumiditySensor(id, minValue.toDouble(), maxValue.toDouble());
		break;
	case AbstractSensor::SensorType::SpeedSensor:
		m_sensor = new SpeedSensor(id, maxValue.toInt());
		break;
	default:
		break;
	}

	connect(this, &AdvSensorItem::updateSensor, m_sensor, &AbstractSensor::update);
}

AbstractSensor* AdvSensorItem::sensor() const
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
		brect.setWidth(240);
		brect.setHeight(200);
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

void AdvSensorItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsObject::mouseMoveEvent(event);
}

void AdvSensorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsObject::mousePressEvent(event);
}

void AdvSensorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsObject::mouseReleaseEvent(event);
}

void AdvSensorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);

	if (m_sensor->type() == AbstractSensor::SensorType::AccelerationSensor)
	{
		const QPointF acceleroCenter(100, 40);

		QPen acceleroCirclePen;
		acceleroCirclePen.setWidth(1);
		acceleroCirclePen.setColor(Qt::gray);

		QRadialGradient accelGrad(acceleroCenter, 60);
		accelGrad.setColorAt(0.2, Qt::black);
		accelGrad.setColorAt(0.6, Qt::darkGray);
		accelGrad.setColorAt(1.0, Qt::gray);

		acceleroCirclePen.setBrush(accelGrad);

		painter->setPen(acceleroCirclePen);

		for(int i = 1; i < 4; ++i)
		{
			painter->drawEllipse(acceleroCenter, i*20, i * 20);
		}

		acceleroCirclePen.setStyle(Qt::DashLine);
		acceleroCirclePen.setDashOffset(3);
		painter->setPen(acceleroCirclePen);

		painter->drawLine(acceleroCenter.x() - 60, acceleroCenter.y(),
						  acceleroCenter.x() + 60, acceleroCenter.y());
		painter->drawLine(acceleroCenter.x(), acceleroCenter.y() - 60,
						  acceleroCenter.x(), acceleroCenter.y() + 60);
		QPointF gpoint;

		const AccelerationSensor*  accsensor = qobject_cast<const AccelerationSensor*>(m_sensor);
		QPointF gvalue = accsensor->value().toPointF();

		const double xpos = acceleroCenter.x() + (gvalue.x() * (60 / accsensor->xMaxAcceleration()));
		const double ypos = acceleroCenter.y() + (gvalue.y() * (60 / accsensor->yMaxAcceleration()));

		gpoint.setX(xpos);
		gpoint.setY(ypos);

		acceleroCirclePen.setDashOffset(0.5);
		QBrush gpointBrush(Qt::darkRed);
		acceleroCirclePen.setStyle(Qt::DashLine);
		acceleroCirclePen.setBrush(gpointBrush);
		acceleroCirclePen.setColor(Qt::white);
		painter->setBrush(gpointBrush);
		painter->setOpacity(1);
		painter->setPen(acceleroCirclePen);
		painter->drawEllipse(gpoint, 4, 4);

		QFont axisValueFont;
		axisValueFont.setPixelSize(10);

		painter->setFont(axisValueFont);
		const QString& xmin = QString::number(accsensor->xMinAcceleration(),'f', 1);
		const QString& xmax = QString::number(accsensor->xMaxAcceleration(),'f', 1);

		painter->drawText(acceleroCenter.x()- 60, acceleroCenter.y() + 11, xmin);
		painter->drawText(acceleroCenter.x()+ 55, acceleroCenter.y() + 11, xmax);
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

		QFont kmhFont;
		kmhFont.setBold(true);
		kmhFont.setPointSize(12);
		painter->setFont(kmhFont);
		painter->drawText(speedoCenter.x() - 27, speedoCenter.y() + 53, "Km/h");
		QPen kmhPen(QColor::fromRgb(13,17,18));

		QBrush kmhBrush(QColor::fromRgb(255, 153, 68));

		QPainterPath textPath;
		kmhPen.setCapStyle(Qt::RoundCap);
		kmhPen.setWidth(3);
		kmhFont.setPointSize(20);
		const int speed = m_sensor->value().toInt();

		if (speed < 100)
		{
			if (speed < 10)
			{
				textPath.addText(speedoCenter.x() - 10, speedoCenter.y() + 87,
								 kmhFont, QString::number(m_sensor->value().toInt()));
			}
			else
			{
				textPath.addText(speedoCenter.x() - 23, speedoCenter.y() + 87,
								 kmhFont, QString::number(m_sensor->value().toInt()));
			}
		}
		else
		{
			textPath.addText(speedoCenter.x() - 32, speedoCenter.y() + 87,
							 kmhFont, QString::number(m_sensor->value().toInt()));
		}


		painter->setPen(kmhPen);
		painter->fillPath(textPath, kmhBrush);
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
		humidityFont.setPointSize(10);
		painter->setFont(humidityFont);
		painter->drawText(0, 5, QLatin1String("Humidity"));

		QBrush fontBrush(QColor::fromRgb(22.7, 22.7, 18.4));
		QPen fontPen;
		fontPen.setBrush(fontBrush);
		painter->setPen(fontPen);

		humidityFont.setPointSize(15);
		humidityFont.setItalic(false);
		painter->setFont(humidityFont);
		QString humidityString = QString::number(m_sensor->value().toDouble(), 'f', 1);
		painter->drawText(10, 55, humidityString + "%");

		QConicalGradient humidityPieGrad;
		humidityPieGrad.setCenter(50, 55);
		humidityPieGrad.setAngle(-15);
		humidityPieGrad.setColorAt(0.0, QColor::fromRgb(255, 93, 63));
		humidityPieGrad.setColorAt(0.4, QColor::fromRgb(255, 184, 63));
		humidityPieGrad.setColorAt(0.7, QColor::fromRgb(71, 90, 207));
		humidityPieGrad.setColorAt(1.0, QColor::fromRgb(70, 70, 221));
		painter->setOpacity(0.6);

		painter->setBrush(humidityPieGrad);
		if (m_sensor->value().toInt() > 0)
			painter->drawPie(0, 10, 95, 95, 360*16, (m_sensor->value().toInt() * 36* 16)/10);
	}

	if (m_sensor->type() == AbstractSensor::SensorType::TemperatureSensor)
	{
		QFont tempFont;

		tempFont.setFamily("arial");
		tempFont.setPointSize(10);
		tempFont.setCapitalization(QFont::Capitalize);
		tempFont.setBold(true);

		painter->setFont(tempFont);
		painter->drawText(0, 0, QLatin1String("Temperature"));

		QBrush tempBrush(QColor(Qt::darkGreen).darker());

		painter->setBrush(tempBrush);
		painter->setOpacity(0.5);

		painter->drawRoundedRect(0, 5, 125, 55, 40, 37);

		tempFont.setItalic(false);

		tempFont.setPointSize(20);
		painter->setFont(tempFont);

		QString temperatureString = QString::number(m_sensor->value().toDouble(),'f', 1);
		painter->drawText(25, 45, temperatureString+ QString::fromUtf8("\u2103"));

		painter->setOpacity(0.8);
		if (m_sensor->value().toDouble() <= 4)
		{
			painter->drawPixmap(125, 10, 40,40, QPixmap(":/pictures/data/coldTempSign.png"));
		}
	}
}
