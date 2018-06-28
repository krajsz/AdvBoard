#include "BluetoothHandler.h"

#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
#ifdef Q_OS_ANDROID
static const QLatin1String reverseUuid("c8e96402-0102-cf9c-274b-701a950fe1e8");
#endif

BluetoothHandler::BluetoothHandler(QObject *parent) : QObject(parent),
	m_serviceDiscoveryAgent(new QBluetoothServiceDiscoveryAgent(QBluetoothLocalDevice().address())),
	m_client(new GPSBluetoothClient)
{
	if (m_serviceDiscoveryAgent->isActive())
		m_serviceDiscoveryAgent->stop();
/*#ifdef Q_OS_ANDROID
	if (QtAndroid::androidSdkVersion() >= 23)
		m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(reverseUuid));
	else
		m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));
#else
	m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));
#endif*/

	m_serviceDiscoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));

	connect(m_serviceDiscoveryAgent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered, this, &BluetoothHandler::newServiceDiscovered);

	m_serviceDiscoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
}

BluetoothHandler::~BluetoothHandler()
{
	delete m_client;
	delete m_serviceDiscoveryAgent;
}

void BluetoothHandler::newServiceDiscovered(const QBluetoothServiceInfo& service)
{
	if (service.device().name() == "raspberrypi")
	{
		emit debugString("newServiceDiscovered, device name raspberrypi");
		if (m_serviceDiscoveryAgent->isActive())
			m_serviceDiscoveryAgent->stop();

		m_client->startClient(service);

		connect(m_client, &GPSBluetoothClient::messageReceived, this,&BluetoothHandler::messageReceived);
		connect(m_client, &GPSBluetoothClient::clientConnected, this, &BluetoothHandler::debugString);
	}
}


