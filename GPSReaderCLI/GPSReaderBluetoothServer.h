#ifndef GPSREADERBLUETOOTHSERVER_H
#define GPSREADERBLUETOOTHSERVER_H

#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothAddress>

#include <QtCore/QObject>
#include <QtCore/QList>

class QBluetoothServer;
class QBluetoothSocket;

class GPSReaderBluetoothServer : public QObject
{
	Q_OBJECT

public:
	explicit GPSReaderBluetoothServer(QObject *parent = 0);
	~GPSReaderBluetoothServer();

	void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
	void stopServer();

public slots:
	void sendMessage(const QString &message);

signals:
	void messageReceived(const QString &sender, const QString &message);
	void clientConnected(const QString &name);
	void clientDisconnected(const QString &name);

private slots:
	void ClientConnectedSlot();
	void clientDisconnectedSlot();
	void readSocket();

private:
	QBluetoothServer *m_btServer;
	QBluetoothServiceInfo m_serviceInfo;
	QList<QBluetoothSocket *> m_clientSockets;
	QBluetoothSocket * m_clientSocket;
};


#endif // GPSREADERBLUETOOTHSERVER_H
