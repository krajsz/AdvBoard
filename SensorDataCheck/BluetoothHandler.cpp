#include "BluetoothHandler.h"

#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
#ifdef Q_OS_ANDROID
static const QLatin1String reverseUuid("c8e96402-0102-cf9c-274b-701a950fe1e8");
#endif

BluetoothHandler::BluetoothHandler(QObject *parent) : QObject(parent),
	m_localDevice(new QBluetoothLocalDevice),
	m_deviceDiscoveryAgent(nullptr),
	m_serviceDiscoveryAgent(nullptr),
	m_client(new GPSBluetoothClient)
{
	/*#ifdef Q_OS_ANDROID
	if (QtAndroid::androidSdkVersion() >= 23)
		m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(reverseUuid));
	else
		m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));
#else
	m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));
#endif*/

	//m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));
	m_localDevice->powerOn();

	m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(m_localDevice->address());
	connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothHandler::newDeviceDiscovered);
	connect(m_deviceDiscoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
		  [=](QBluetoothDeviceDiscoveryAgent::Error error){	Q_UNUSED(error);
							emit debugString( m_deviceDiscoveryAgent->errorString());
							});

	m_deviceDiscoveryAgent->start();
}

BluetoothHandler::~BluetoothHandler()
{
	delete m_client;
	delete m_deviceDiscoveryAgent;

	if (m_serviceDiscoveryAgent)
		delete m_serviceDiscoveryAgent;

	delete m_localDevice;
}

void BluetoothHandler::newDeviceDiscovered(const QBluetoothDeviceInfo &device)
{
	emit debugString("newDeviceDiscovered: " + device.name());

	if (device.name() == QLatin1String("raspberrypi"))
	{
		if (m_serviceDiscoveryAgent == nullptr)
		{
			m_serviceDiscoveryAgent = new QBluetoothServiceDiscoveryAgent(m_localDevice->address());
		}
		connect(m_serviceDiscoveryAgent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered, this, &BluetoothHandler::newServiceDiscovered);

		connect(m_serviceDiscoveryAgent, QOverload<QBluetoothServiceDiscoveryAgent::Error>::of(&QBluetoothServiceDiscoveryAgent::error),
			  [=](QBluetoothServiceDiscoveryAgent::Error error){ Q_UNUSED(error);
			emit debugString( m_serviceDiscoveryAgent->errorString()); });

		//m_serviceDiscoveryAgent->setRemoteAddress(device.address());
		m_serviceDiscoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
		emit debugString("serviceDiscovery started");
	}
}

void BluetoothHandler::newServiceDiscovered(const QBluetoothServiceInfo& service)
{
	emit debugString("!!!newServiceDiscovered, device name raspberrypi");

	if (service.serviceUuid() == QBluetoothUuid(serviceUuid))
	{
		if (m_serviceDiscoveryAgent->isActive())
			m_serviceDiscoveryAgent->stop();
		emit debugString("newServiceDiscovered, raspberry, uuid matches");

		m_client->startClient(service);

		connect(m_client, &GPSBluetoothClient::messageReceived, this,&BluetoothHandler::messageReceived);
		connect(m_client, &GPSBluetoothClient::clientConnected, this, &BluetoothHandler::debugString);
	}
	else
	{
		emit debugString("serviceDiscovery uuid doesn't match: "+ service.serviceName() + " uuid" + service.serviceUuid().toString());
	}
}


