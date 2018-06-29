
#include "GPSReaderBluetoothServer.h"

#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothLocalDevice>

#include <QDebug>

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

GPSReaderBluetoothServer::GPSReaderBluetoothServer(QObject *parent)
:   QObject(parent), m_btServer(nullptr),
  m_localDevice(new QBluetoothLocalDevice)
{
	m_localDevice->powerOn();
	m_localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
	startServer(m_localDevice->address());
}

GPSReaderBluetoothServer::~GPSReaderBluetoothServer()
{
	stopServer();
}

void GPSReaderBluetoothServer::startServer(const QBluetoothAddress& localAdapter)
{
	if (m_btServer)
		return;

	m_btServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
	connect(m_btServer, &QBluetoothServer::newConnection, this, &GPSReaderBluetoothServer::clientDisconnectedSlot);
	bool result = m_btServer->listen(localAdapter);
	if (!result) {
		qWarning() << "Cannot bind chat server to" << localAdapter.toString();
		return;
	} else
	{
		qDebug() << "Server listening on: " << localAdapter.toString();
	}

	//serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceRecordHandle, (uint)0x00010010);

	QBluetoothServiceInfo::Sequence classId;

	classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
							 classId);

	classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);

	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("GPSDataReader"));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
							 tr("Checking GPS data sent from the RPi"));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("krajsz"));

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
			 << QVariant::fromValue(quint8(m_btServer->serverPort()));
	protocolDescriptorList.append(QVariant::fromValue(protocol));
	m_serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
							 protocolDescriptorList);

	m_serviceInfo.registerService(localAdapter);
}

void GPSReaderBluetoothServer::stopServer()
{
	m_serviceInfo.unregisterService();

	qDeleteAll(m_clientSockets);

	delete m_btServer;
	m_btServer = 0;

	qDebug() << "stop server";
}

void GPSReaderBluetoothServer::sendMessage(const QString &message)
{
	QByteArray text = message.toUtf8() + '\n';

	foreach (QBluetoothSocket *socket, m_clientSockets)
		socket->write(text);

	qDebug() << "sending message";
}

void GPSReaderBluetoothServer::clientConnectedSlot()
{
	QBluetoothSocket *socket = m_btServer->nextPendingConnection();
	if (!socket)
		return;

	qDebug() << "clientConnected";

	connect(socket, &QBluetoothSocket::readyRead, this, &GPSReaderBluetoothServer::readSocket);
	connect(socket, &QBluetoothSocket::disconnected, this, &GPSReaderBluetoothServer::clientDisconnectedSlot);
	m_clientSockets.append(socket);
	emit clientConnected(socket->peerName());
}

void GPSReaderBluetoothServer::clientDisconnectedSlot()
{
	QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
	if (!socket)
		return;

	emit clientDisconnected(socket->peerName());

	m_clientSockets.removeOne(socket);

	socket->deleteLater();
}

void GPSReaderBluetoothServer::readSocket()
{
	QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
	if (!socket)
		return;

	while (socket->canReadLine()) {
		QByteArray line = socket->readLine().trimmed();
		emit messageReceived(socket->peerName(),
							 QString::fromUtf8(line.constData(), line.length()));
	}
}

