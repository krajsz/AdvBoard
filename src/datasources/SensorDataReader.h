#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QObject>
#include <QFileSystemWatcher>

class QTimer;
class QFileSystemWatcher;

class SensorDataReader : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataReader(QObject *parent);
    SensorDataReader(const SensorData&) = delete;

    virtual void read();

private:
    QString m_path;
    QFileSystemWatcher* m_fileWatcher;
    QTimer* m_readTimer;

    int m_interval;
};

#endif // SENSORDATA_H
