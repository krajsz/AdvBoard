#include "BluetoothDataSender.h"

#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothUuid>

#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QDebug>
static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

BluetoothDataSender::BluetoothDataSender(QObject *parent) :QObject(parent),
	m_localDevice(new QBluetoothLocalDevice),
	m_bluetoothServer(new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this))
{
	const QBluetoothAddress& address = m_localDevice->address();

	m_bluetoothDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(address);

	connect(m_bluetoothDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothDataSender::deviceDiscovered);
	connect(m_bluetoothServer, &QBluetoothServer::newConnection, this, &BluetoothDataSender::newConnection);

	m_localDevice->powerOn();
	m_bluetoothDiscoveryAgent->start();

	if (!m_bluetoothServer->listen(m_localDevice->address()))
	{
		qDebug() << "Cannot bind server to " << m_localDevice->address().toString();
	}

	QBluetoothServiceInfo::Sequence classId;

	classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
							 classId);

	classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);

	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("GPSReader"));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
							 tr("GPS bluetooth server"));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("qt-project.org"));

	m_serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));

	QBluetoothServiceInfo::Sequence publicBrowse;
	publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
							 publicBrowse);

	QBluetoothServiceInfo::Sequence protocolDescriptorList;
	QBluetoothServiceInfo::Sequence protocol;
	protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
	protocolDescriptorList.append(QVariant::fromValue(protocol));
	protocol.clear();
	protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
			 << QVariant::fromValue(quint8(m_bluetoothServer->serverPort()));
	protocolDescriptorList.append(QVariant::fromValue(protocol));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
							 protocolDescriptorList);

	m_serviceInfo.registerService(m_localDevice->address());

	qDebug() << "Local device name: " << m_localDevice->name() << " address: " << m_localDevice->address();
}

void BluetoothDataSender::newConnection()
{
	QBluetoothSocket *socket = m_bluetoothServer->nextPendingConnection();

	qDebug() << socket->peerName();
}

BluetoothDataSender::~BluetoothDataSender()
{
	delete m_localDevice;
	delete m_bluetoothDiscoveryAgent;
}

void BluetoothDataSender::deviceDiscovered(const QBluetoothDeviceInfo &btdevice)
{
	qDebug() << "New device: " << btdevice.name() << " address: " << btdevice.address();
}
