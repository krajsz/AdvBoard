/***************************************************************************
File		: AbstractSensor.cpp
Project		: AdvBoard
Description	: Base class for sensors
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/sensors/AccelerationSensor.h"
#include "src/sensors/GPSpositionSensor.h"
#include "src/sensors/HumiditySensor.h"
#include "src/sensors/SpeedSensor.h"
#include "src/sensors/TemperatureSensor.h"
#include "src/sensors/AbstractSensor.h"

/***********************************************************************/
#include <QDebug>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPointF>
#include <QVariant>
#include <QJsonObject>
AbstractSensor::AbstractSensor(const int id,const QVariant& minValue, const QVariant& maxValue, const QVariant &val, AbstractSensor::SensorType type, QObject *parent) :
	QObject(parent), m_id(id),
	m_minValue(minValue), m_maxValue(maxValue), m_value(val), m_type(type),
	m_animation(new QVariantAnimation(this)),
	m_drawingPosition(AbstractSensor::Separate)
{
	connect(m_animation, &QVariantAnimation::valueChanged, this, &AbstractSensor::setValue);
}

bool AbstractSensor::operator ==(const AbstractSensor& other) const
{
	return (other.m_id == this->m_id) && (other.type() == this->type());
}

AbstractSensor::~AbstractSensor()
{
	delete m_animation;
}

QVariantAnimation *AbstractSensor::animation()
{
	return m_animation;
}

void AbstractSensor::update(const QVariant &newvalue)
{
	m_animation->stop();

	m_animation->setStartValue(m_value);
	m_animation->setEndValue(newvalue);

	m_animation->start();
	m_value = newvalue;

	emit sensorUpdated();
}

QVariant AbstractSensor::value() const
{
	return m_value;
}

QVariant AbstractSensor::minValue() const
{
	return m_minValue;
}

QVariant AbstractSensor::maxValue() const
{
	return m_maxValue;
}

AbstractSensor::DrawingPosition AbstractSensor::drawingPosition() const
{
	return m_drawingPosition;
}

void AbstractSensor::setDrawingPosition(const DrawingPosition position)
{
	m_drawingPosition = position;
}

void AbstractSensor::setValue(const QVariant &newValue)
{
	m_value = newValue;
}

int AbstractSensor::id() const
{
	return m_id;
}

AbstractSensor::SensorType AbstractSensor::type() const
{
	return m_type;
}

