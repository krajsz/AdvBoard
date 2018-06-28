#ifndef BLUETOOTHHANDLER_H
#define BLUETOOTHHANDLER_H

#include <QObject>

#include "GPSBluetoothClient.h"

class QBluetoothServiceDiscoveryAgent;
class QBluetoothServiceInfo;

class BluetoothHandler : public QObject
{
	Q_OBJECT
public:
	BluetoothHandler(QObject* parent = nullptr);
	virtual ~BluetoothHandler();

private:
	GPSBluetoothClient* m_client;
	QBluetoothServiceDiscoveryAgent* m_serviceDiscoveryAgent;

private slots:
	void newServiceDiscovered(const QBluetoothServiceInfo& service);
signals:
	void debugString(const QString& dbg);
	void messageReceived(const QString& sender,const QString& message);
};

#endif // BLUETOOTHHANDLER_H
