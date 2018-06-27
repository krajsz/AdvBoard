#include "BluetoothDataSender.h"

#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothSocket>

#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QDebug>

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
