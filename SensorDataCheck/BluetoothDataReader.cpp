#include "BluetoothDataReader.h"

#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/QBluetoothLocalDevice>

BluetoothDataReader::BluetoothDataReader(QObject *parent) : QObject(parent),
	m_localDevice(new QBluetoothLocalDevice)
{
	const QBluetoothAddress& address = m_localDevice->address();

	m_bluetoothDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(address);
	connect(m_bluetoothDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothDataReader::deviceDiscovered);

	connect(m_bluetoothDiscoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error), this,
		[=](QBluetoothDeviceDiscoveryAgent::Error error){ emit discoveryError(m_bluetoothDiscoveryAgent->errorString()); });
	m_localDevice->powerOn();

	m_bluetoothDiscoveryAgent->start();
}

void BluetoothDataReader::deviceDiscovered(const QBluetoothDeviceInfo &btdevice)
{
	emit newDevice(btdevice.name());
}

void BluetoothDataReader::deviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error)
{
	Q_UNUSED(error)
	emit discoveryError(m_bluetoothDiscoveryAgent->errorString());
}
