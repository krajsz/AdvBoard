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
class LiveSensorDataReader : public SensorDataReader
{
    Q_OBJECT
public:
    explicit LiveSensorDataReader(QObject* parent = Q_NULLPTR);
    void read();
    void setDevice(QIODevice* device);
    void setFile(const QString &path);
private:
    QIODevice* m_device;

    QFileSystemWatcher* m_fileWatcher;
    QLocalSocket* m_localSocket;
    QTcpSocket* m_tcpSocket;
};

#endif // LIVESENSORDATAREADER_H
