#ifndef BLUETOOTHDATAREADER_H
#define BLUETOOTHDATAREADER_H

#include <QObject>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

class QBluetoothLocalDevice;
class QBluetoothDeviceInfo;
class BluetoothDataReader : public QObject
{
	Q_OBJECT
public:
	explicit BluetoothDataReader(QObject* parent = nullptr);
private:
	QBluetoothDeviceDiscoveryAgent * m_bluetoothDiscoveryAgent;
	QBluetoothLocalDevice* m_localDevice;
private slots:
	void deviceDiscovered(const QBluetoothDeviceInfo& btdevice);
	void deviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error);
signals:
	void discoveryError(const QString& error);
	void newDevice(const QString& name);
};

#endif // BLUETOOTHDATAREADER_H
