#include "GPSReader.h"

#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtPositioning/QNmeaPositionInfoSource>
#include <QtPositioning/QGeoPositionInfo>

GPSReader::GPSReader(QObject *parent) : QObject(parent),
	m_device(nullptr),
	m_testGPSDataFile(new QFile(":/data/gpsData.txt"))
{
	m_dataSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::UpdateMode::SimulationMode);
	m_dataSource->setDevice(m_testGPSDataFile);
	m_dataSource->setUpdateInterval(2000);

	connect(m_dataSource, &QNmeaPositionInfoSource::positionUpdated, this, &GPSReader::newPosition);

	m_dataSource->startUpdates();
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
}
