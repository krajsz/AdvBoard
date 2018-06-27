#include "BluetoothDataSender.h"

#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QDebug>

BluetoothDataSender::BluetoothDataSender(QObject *parent) :QObject(parent),
	m_localDevice(new QBluetoothLocalDevice)
{
	const QBluetoothAddress& address = m_localDevice->address();

	m_bluetoothDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(address);

	connect(m_bluetoothDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothDataSender::deviceDiscovered);

	m_localDevice->powerOn();
	m_bluetoothDiscoveryAgent->start();

	qDebug() << "Local device name: " << m_localDevice->name() << " address: " << m_localDevice->address();
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
