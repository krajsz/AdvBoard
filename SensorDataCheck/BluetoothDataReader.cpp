#include "BluetoothDataReader.h"

#include <QtBluetooth/QBluetoothDeviceInfo>

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

BluetoothDataReader::~BluetoothDataReader()
{
	delete m_localDevice;
	delete m_bluetoothDiscoveryAgent;
}

void BluetoothDataReader::deviceDiscovered(const QBluetoothDeviceInfo &btdevice)
{
	emit newDevice(btdevice.name());

	if (btdevice.name() == "raspberrypi")
	{
		emit debugString("deviceDiscovered, device raspberry");

		m_localDevice->requestPairing(btdevice.address(), QBluetoothLocalDevice::Paired);
		connect(m_localDevice, &QBluetoothLocalDevice::pairingFinished, this, &BluetoothDataReader::pairingFinished);
	}
}

void BluetoothDataReader::pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
	emit debugString("pairingFinished, pairing:" + QString::number(pairing));

	for (const auto& deviceInfo: m_bluetoothDiscoveryAgent->discoveredDevices())
	{
		if (deviceInfo.address() == address)
		{
			if (deviceInfo.name() == "raspberrypi")
			{
				emit debugString("pairingFinished, device raspberry");
			}
		}
	}

	if (pairing == QBluetoothLocalDevice::Pairing::AuthorizedPaired)
	{
		emit paired(true);
	}
	else
	{
		emit paired(false);
	}
}

void BluetoothDataReader::deviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error)
{
	Q_UNUSED(error)
	emit debugString("deviceDiscoveryError, error:" + QString::number(error));

	emit discoveryError(m_bluetoothDiscoveryAgent->errorString());
}
