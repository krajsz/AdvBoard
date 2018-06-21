#include "GPSWindow.h"
#include "ui_gpswindow.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QtPositioning/QGeoPositionInfo>
#include <QStringList>

GPSWindow::GPSWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::GPSWindow),
	m_gpsReader(new GPSReader)
{
	ui->setupUi(this);

	connect(ui->serialPortComboBox, &QComboBox::currentTextChanged, m_gpsReader, &GPSReader::setSerialPort);
	QList<QSerialPortInfo> lports = QSerialPortInfo::availablePorts();

	QStringList ports;
	for(const QSerialPortInfo& info : lports)
	{
		ports << info.portName();
	}

	ui->serialPortComboBox->addItems(ports);

	connect(m_gpsReader, &GPSReader::newPosition, this, &GPSWindow::updateInfo);
}

void GPSWindow::updateInfo(const QGeoPositionInfo &info)
{
	ui->altitudeLabel->setText("Alt: " + QString::number(info.coordinate().altitude()));
	ui->latituteLabel->setText("Lat: " + QString::number(info.coordinate().latitude()));
	ui->longitudeLabel->setText("Lon: " + QString::number(info.coordinate().longitude()));
	ui->timestampLabel->setText("Timestamp: " + info.timestamp().toString());
	if (info.hasAttribute(QGeoPositionInfo::Attribute::GroundSpeed))
	{
		ui->speedLabel->setText("Speed: " + QString::number(info.attribute(QGeoPositionInfo::Attribute::GroundSpeed)) + "m/s");
	}
	else if (info.hasAttribute(QGeoPositionInfo::Attribute::VerticalSpeed))
	{
		ui->speedLabel->setText("SpeedV: " + QString::number(info.attribute(QGeoPositionInfo::Attribute::VerticalSpeed)) + "m/s");
	}
}

GPSWindow::~GPSWindow()
{
	delete ui;
}
