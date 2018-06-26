#include "GPSReader.h"

#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtPositioning/QNmeaPositionInfoSource>
#include <QtPositioning/QGeoPositionInfo>

#include <QDebug>

GPSReader::GPSReader(QObject *parent) : QObject(parent),
	m_device(nullptr),
	m_testGPSDataFile(new QFile(":/data/gpsData.txt"))
{
	m_dataSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::UpdateMode::SimulationMode);
	m_dataSource->setUpdateInterval(2000);

	connect(m_dataSource, &QNmeaPositionInfoSource::positionUpdated, this, &GPSReader::newPosition);
}

void GPSReader::setSerialPort(const QString& port)
{
	if(m_device == nullptr)
	{
		m_device = new QSerialPort(port);
	}
	else
	{
		m_device->setPortName(port);
	}
	if (m_device->portName() == "ttyS0")
	{
		m_dataSource->setDevice(m_device);
		m_dataSource->startUpdates();
		qDebug() << "ttyS0";
	}
}
