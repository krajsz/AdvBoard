#ifndef GPSREADER_H
#define GPSREADER_H

#include <QObject>

class QFile;
class QSerialPort;
class QNmeaPositionInfoSource;
class QGeoPositionInfo;
class BluetoothDataSender;
class GPSReaderBluetoothServer;

class GPSReader : public QObject
{
	Q_OBJECT
public:
	explicit GPSReader(QObject *parent = nullptr);

	virtual ~GPSReader();
public slots:
	void setSerialPort(const QString& port);
private slots:
	void newPosition(const QGeoPositionInfo& info);

	void debugString(const QString& str);
	void clientConnected(const QString& name);
private:
	QSerialPort* m_device;
	QFile* m_testGPSDataFile;
	QNmeaPositionInfoSource* m_dataSource;

	GPSReaderBluetoothServer* m_btServer;

public slots:
};

#endif // GPSREADER_H
