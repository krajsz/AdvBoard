#ifndef BLUETOOTHDATASENDER_H
#define BLUETOOTHDATASENDER_H

#include <QObject>

class QBluetoothServer;
class QBluetoothServiceDiscoveryAgent;
class QBluetoothLocalDevice;
class QBluetoothDeviceInfo;
class QBluetoothDeviceDiscoveryAgent;

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
public slots:

private slots:
	void deviceDiscovered(const QBluetoothDeviceInfo& btdevice);

};

#endif // BLUETOOTHDATASENDER_H
