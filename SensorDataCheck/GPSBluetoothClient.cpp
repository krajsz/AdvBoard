
#include "GPSBluetoothClient.h"

#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothSocket>

GPSBluetoothClient::GPSBluetoothClient(QObject *parent)
:   QObject(parent), m_socket(nullptr)
{
}

GPSBluetoothClient::~GPSBluetoothClient()
{
	stopClient();
}

void GPSBluetoothClient::startClient(const QBluetoothServiceInfo &remoteService)
{
	if (m_socket)
		return;

	m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
	m_socket->connectToService(remoteService);

	connect(m_socket, &QBluetoothSocket::readyRead, this, &GPSBluetoothClient::readSocket);
	connect(m_socket, &QBluetoothSocket::connected, this, &GPSBluetoothClient::connected);
	connect(m_socket, &QBluetoothSocket::disconnected, this, &GPSBluetoothClient::disconnected);
}

void GPSBluetoothClient::stopClient()
{
	delete m_socket;
	m_socket = 0;
}

void GPSBluetoothClient::readSocket()
{
	if (!m_socket)
		return;

	while (m_socket->canReadLine())
	{
		QByteArray line = m_socket->readLine();
		emit messageReceived(m_socket->peerName(),
							 QString::fromUtf8(line.constData(), line.length()));
	}
}

void GPSBluetoothClient::sendMessage(const QString &message)
{
	const QByteArray text = message.toUtf8() + '\n';
	m_socket->write(text);
}

void GPSBluetoothClient::connected()
{
	emit clientConnected(m_socket->peerName());
}
