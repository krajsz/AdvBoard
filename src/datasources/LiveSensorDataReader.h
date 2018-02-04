/***************************************************************************
File		: LiveSensorDataReader.h
Project		: AdvBoard
Description	: Class for reading live sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef LIVESENSORDATAREADER_H
#define LIVESENSORDATAREADER_H

#include "SensorDataReader.h"

#include <QTcpSocket>
#include <QLocalSocket>
#include <QObject>

class QIODevice;
class QTcpSocket;
class QLocalSocket;
class LiveSensorDataReader final: public SensorDataReader
{
    Q_OBJECT
public:
    explicit LiveSensorDataReader(QObject* parent = Q_NULLPTR);
    ~LiveSensorDataReader() final;
    void read(bool init = false ) override final;

    void setPort(const int port);
    void setHost(const QString& host);

    void setDevice(QIODevice* device);
    void setFile(const QString &path) final override;
    enum SourceType {
        File = 0,
        TCP
    };
    SourceType sourceType() const;
    void setSourceType(const SourceType type);
private slots:
    void fileRead(const QString&filepath);
    void tcpRead();

private:
    QIODevice* m_device;
    SourceType m_sourceType;

    QFileSystemWatcher* m_fileWatcher;
    QLocalSocket* m_localSocket;
    QTcpSocket* m_tcpSocket;

    QString m_host;
    int m_port;
    void readTcpData();

};

#endif // LIVESENSORDATAREADER_H
