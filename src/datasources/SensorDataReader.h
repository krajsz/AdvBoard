/***************************************************************************
File		: SensorDataReader.h
Project		: AdvBoard
Description	: Class for reading sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORDATAREADER_H
#define SENSORDATAREADER_H

#include <QObject>
#include <QVector>

#include <QJsonArray>

#include "src/dashboards/AbstractDashboard.h"
#include "src/datasources/validators/SensorDataSourceValidator.h"

class QTimer;
class QFileSystemWatcher;
class QFile;
class SensorDataReader : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataReader(QObject *parent = nullptr);
    ~SensorDataReader();
    virtual void setFile(const QString& path);
    virtual void read(bool init = false);
    int dataSnapshotCount() const;
    int dashboardType() const;
    int interval() const;
    QVector<QJsonObject> sensorData() const;

	static AbstractSensor* sensorFromData(const QJsonObject& sensorData);

signals:
    void dataRead(const QVector<QJsonValue>& data);
    void initSensors(const QVector<QJsonObject>& sensordata, const int animationDuration);
    void initDashBoard(int dashboardType);
    void dataInvalid(const QString& errorString);
    void dashboardValid(bool valid = true);

    void sensorDataIsValid(bool valid);
public slots:
    virtual void startReading();
protected:
    QFile* m_file;
    QTimer* m_readTimer;
    QVector<QJsonArray> m_data;

    SensorDataSourceValidator* m_sensorDataSourceValidator;

    int m_sensorCount;
    int m_interval;

    void readSnapshot(const int idx);
private slots:
    virtual void readSnapshotSlot();
private:
    QString m_path;
    QVector<QJsonObject> m_sensorData;

    int m_dashboardType;
    int m_dataSnapshotCount;
    int m_dataIndex;
};

#endif // SENSORDATAREADER_H
