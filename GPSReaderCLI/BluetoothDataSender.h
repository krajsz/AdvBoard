#ifndef BLUETOOTHDATASENDER_H
#define BLUETOOTHDATASENDER_H

#include <QObject>

class QBluetoothServer;
class QBluetoothServiceDiscoveryAgent;
class QBluetoothLocalDevice;
class QBluetoothDeviceInfo;
class QBluetoothServiceInfo;
class QBluetoothDeviceDiscoveryAgent;

#include <QtBluetooth/QBluetoothServiceInfo>

class BluetoothDataSender : public QObject
{
	Q_OBJECT
public:
	explicit BluetoothDataSender(QObject* parent = nullptr);
	virtual ~BluetoothDataSender() override;

private:
	QBluetoothServer* m_bluetoothServer;
	QBluetoothDeviceDiscoveryAgent * m_bluetoothDiscoveryAgent;
	QBluetoothLocalDevice* m_localDevice;

	QBluetoothServiceInfo m_serviceInfo;
public slots:

private slots:
	void deviceDiscovered(const QBluetoothDeviceInfo& btdevice);
	void newConnection();
};

#endif // BLUETOOTHDATASENDER_H
