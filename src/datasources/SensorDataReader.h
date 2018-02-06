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
#include "src/datasources/SensorDataValidator.h"

class QTimer;
class QFileSystemWatcher;
class QFile;
class SensorDataReader : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataReader(QObject *parent = nullptr);

    virtual void setFile(const QString& path);
    virtual void read(bool init = false);
    int dataSnapshotCount() const;
signals:
    void dataRead(const QVector<QJsonValue>& data);
    void initSensors(const QVector<QJsonObject>& sensordata, const int animationDuration);
    void initDashBoard(int dashboardType);
    void dataInvalid(const QString& errorString);
    void dashboardValid(bool valid = true);
public slots:
    virtual void startReading();
protected:
    QFile* m_file;
    QTimer* m_readTimer;
    QVector<QJsonArray> m_data;

    SensorDataValidator* m_sensorDataValidator;

    int m_sensorCount;
    int m_interval;

    void readSnapshot(const int idx);
private slots:
    virtual void readSnapshotSlot();
private:
    QString m_path;



    int m_dataSnapshotCount;
    int m_dataIndex;
};

#endif // SENSORDATAREADER_H
