#ifndef GPSREADER_H
#define GPSREADER_H

#include <QObject>

class QFile;
class QSerialPort;
class QNmeaPositionInfoSource;
class QGeoPositionInfo;
class BluetoothDataSender;

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
private:
	QSerialPort* m_device;
	QFile* m_testGPSDataFile;
	QNmeaPositionInfoSource* m_dataSource;
	BluetoothDataSender* m_btDataSender;
public slots:
};

#endif // GPSREADER_H
