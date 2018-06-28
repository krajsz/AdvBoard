#ifndef BLUETOOTHDATAREADER_H
#define BLUETOOTHDATAREADER_H

#include <QObject>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

class QBluetoothDeviceInfo;
class BluetoothDataReader : public QObject
{
	Q_OBJECT
public:
	explicit BluetoothDataReader(QObject* parent = nullptr);
	virtual ~BluetoothDataReader() override;
private:
	QBluetoothDeviceDiscoveryAgent * m_bluetoothDiscoveryAgent;
	QBluetoothLocalDevice* m_localDevice;
private slots:
	void deviceDiscovered(const QBluetoothDeviceInfo& btdevice);
	void deviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error);
	void pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);

signals:
	void discoveryError(const QString& error);
	void newDevice(const QString& name);
	void paired(bool paired);

	void debugString(const QString& str);
};

#endif // BLUETOOTHDATAREADER_H
