/***************************************************************************
File		: LiveSensorDataReader.cpp
Project		: AdvBoard
Description	: Class for reading live sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/LiveSensorDataReader.h"

#include <QFileSystemWatcher>
#include <QIODevice>
#include <QTcpSocket>
#include <QLocalSocket>
#include <QFile>
#include <QHostAddress>
LiveSensorDataReader::LiveSensorDataReader(QObject *parent) : SensorDataReader(parent),
    m_fileWatcher(nullptr),
    m_localSocket(nullptr),
    m_device(nullptr),
    m_tcpSocket(nullptr)
{
}

LiveSensorDataReader::~LiveSensorDataReader()
{
    if (m_fileWatcher)
        delete m_fileWatcher;
    if (m_localSocket)
        delete m_localSocket;
    if (m_tcpSocket)
        delete m_tcpSocket;

}

LiveSensorDataReader::SourceType LiveSensorDataReader::sourceType() const
{
    return m_sourceType;
}

void LiveSensorDataReader::setSourceType(const LiveSensorDataReader::SourceType type)
{
    m_sourceType = type;
}
void LiveSensorDataReader::setDevice(QIODevice *device)
{
    m_device = device;
}

void LiveSensorDataReader::setHost(const QString &host)
{
    m_host = host;
}

void LiveSensorDataReader::setPort(const int port)
{
    m_port = port;
}

void LiveSensorDataReader::fileRead(const QString &filepath)
{
    read();
    Q_UNUSED(filepath)
}

void LiveSensorDataReader::tcpRead()
{
    //read tcp data
}

void LiveSensorDataReader::read(bool init)
{
    if (init)
    {
        switch (m_sourceType)
        {
        case LiveSensorDataReader::SourceType::File:

            connect(m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &LiveSensorDataReader::fileRead);

            break;
        case LiveSensorDataReader::SourceType::TCP:

            m_tcpSocket = new QTcpSocket(this);
            m_tcpSocket->connectToHost(m_host, m_port, QIODevice::ReadOnly);
            connect(m_tcpSocket, &QTcpSocket::readyRead, this, &LiveSensorDataReader::tcpRead);
            break;
        default:
            break;
        }
    }

    switch (m_sourceType)
    {
    case LiveSensorDataReader::SourceType::File:
        SensorDataReader::read();
        SensorDataReader::readSnapshot(0);
        break;
    case LiveSensorDataReader::SourceType::TCP:

        m_tcpSocket->abort();
        m_tcpSocket->connectToHost(m_host, m_port, QIODevice::ReadOnly);

        break;
    default:
        break;
    }
}

void LiveSensorDataReader::setFile(const QString &path)
{
    SensorDataReader::setFile(path);
    m_fileWatcher->addPath(path);
}
