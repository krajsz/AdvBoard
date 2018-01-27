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

class QTimer;
class QFileSystemWatcher;
class QFile;
class SensorDataReader : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataReader(QObject *parent = nullptr);

    virtual void setFile(const QString& path);
    virtual void read();
    int dataSnapshotCount() const;
signals:
    void dataRead(const QVector<QVariant>& data);
    void initSensors(const QVector<QJsonObject>& sensordata);
    void initDashBoard(int sensors, int dashboardType);
    void dataInvalid(const QString& errorString);
public slots:
    void startReading();
protected:
    QFile* m_file;
    QFileSystemWatcher* m_fileWatcher;
    QTimer* m_readTimer;
    QVector<QJsonArray> m_data;

private:
    QString m_path;

    int m_interval;
    int m_dataSnapshotCount;
    int m_sensorCount;

    int m_dataIndex;
    void readSnapshot();
};

#endif // SENSORDATAREADER_H
