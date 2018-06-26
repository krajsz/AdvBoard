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
	m_dataSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::UpdateMode::RealTimeMode);
	m_dataSource->setUpdateInterval(2000);

	connect(m_dataSource, &QNmeaPositionInfoSource::positionUpdated, this, &GPSReader::newPosition);

	setSerialPort("ttyS0");
}

void GPSReader::newPosition(const QGeoPositionInfo &info)
{
	qDebug() << info;


	qDebug() << "Alt: " << info.coordinate().altitude();
	qDebug() << "Lat: " << info.coordinate().latitude();
	qDebug() << "Lon: " << info.coordinate().longitude();
	qDebug() << "Timestamp: " << info.timestamp().toString();
	if (info.hasAttribute(QGeoPositionInfo::Attribute::GroundSpeed))
	{
		qDebug() << "Speed: " << info.attribute(QGeoPositionInfo::Attribute::GroundSpeed) << "m/s";
	}
	else if (info.hasAttribute(QGeoPositionInfo::Attribute::VerticalSpeed))
	{
		qDebug() <<"SpeedV: " << info.attribute(QGeoPositionInfo::Attribute::VerticalSpeed) << "m/s";
	}
}

GPSReader::~GPSReader()
{
	if (m_device)
		delete m_device;

	if (m_dataSource)
		delete m_dataSource;
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
