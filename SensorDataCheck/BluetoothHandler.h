#ifndef BLUETOOTHHANDLER_H
#define BLUETOOTHHANDLER_H

#include <QObject>

#include "GPSBluetoothClient.h"

class QBluetoothServiceDiscoveryAgent;
class QBluetoothDeviceDiscoveryAgent;
class QBluetoothServiceInfo;
class QBluetoothDeviceInfo;
class QBluetoothLocalDevice;

class BluetoothHandler : public QObject
{
	Q_OBJECT
public:
	BluetoothHandler(QObject* parent = nullptr);
	virtual ~BluetoothHandler();

private:
	GPSBluetoothClient* m_client;
	QBluetoothServiceDiscoveryAgent* m_serviceDiscoveryAgent;
	QBluetoothDeviceDiscoveryAgent* m_deviceDiscoveryAgent;

	QBluetoothLocalDevice* m_localDevice;

private slots:
	void newServiceDiscovered(const QBluetoothServiceInfo& service);
	void newDeviceDiscovered(const QBluetoothDeviceInfo& device);
signals:
	void debugString(const QString& dbg);
	void messageReceived(const QString& sender,const QString& message);
};

#endif // BLUETOOTHHANDLER_H
