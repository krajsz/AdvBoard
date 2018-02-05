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
#include <QJsonDocument>
#include <QTimer>

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

void LiveSensorDataReader::startReading()
{
    if (m_sourceType == LiveSensorDataReader::SourceType::File)
    {
        connect(m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &LiveSensorDataReader::fileRead);

    }
    else if (m_sourceType == LiveSensorDataReader::SourceType::TCP)
    {
        if (m_readTimer)
            m_readTimer->start(m_interval);
    }
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

void LiveSensorDataReader::readSnapshotSlot()
{
    read();
}

void LiveSensorDataReader::tcpRead()
{
    //read tcp data
    if (!(m_tcpSocket->bytesAvailable() > 0))
    {
        return;
    }

    const QByteArray jsonBytes = m_tcpSocket->readAll();
    const QJsonDocument newSensorDataDocument = QJsonDocument::fromJson(jsonBytes);
    const QJsonObject& sensorDataObject = newSensorDataDocument.object();
    const QJsonArray& sensorDataArray = sensorDataObject["sensorData"].toArray();

    QVector<QJsonValue> dataToSend;
    dataToSend.reserve(m_sensorCount);

    for (int i = 0; i < sensorDataArray.size(); ++i)
    {
        dataToSend.push_back(sensorDataArray[i]);
    }
    emit dataRead(dataToSend);
}

void LiveSensorDataReader::read(bool init)
{
    if (init)
    {
        switch (m_sourceType)
        {
        case LiveSensorDataReader::SourceType::File:


            break;
        case LiveSensorDataReader::SourceType::TCP:

            m_tcpSocket = new QTcpSocket(this);
            m_tcpSocket->connectToHost(m_host, m_port, QIODevice::ReadOnly);
            connect(m_tcpSocket, &QTcpSocket::readyRead, this, &LiveSensorDataReader::tcpRead);
            connect(m_readTimer, &QTimer::timeout, this, &LiveSensorDataReader::readSnapshotSlot);
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
