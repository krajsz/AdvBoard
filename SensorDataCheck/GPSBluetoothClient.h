#ifndef GPSBLUETOOTHCLIENT_H
#define GPSBLUETOOTHCLIENT_H

#include <QtBluetooth/QBluetoothServiceInfo>

#include <QtCore/QObject>


class QBluetoothSocket;

class GPSBluetoothClient : public QObject
{
	Q_OBJECT

public:
	explicit GPSBluetoothClient(QObject *parent = 0);
	~GPSBluetoothClient();

	void startClient(const QBluetoothServiceInfo &remoteService);
	void stopClient();

public slots:
	void sendMessage(const QString &message);

signals:
	void messageReceived(const QString &sender, const QString &message);
	void clientConnected(const QString &name);
	void disconnected();

private slots:
	void readSocket();
	void connected();

private:
	QBluetoothSocket *m_socket;
};

#endif // GPSBLUETOOTHCLIENT_H
