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

LiveSensorDataReader::LiveSensorDataReader(QObject *parent) : SensorDataReader(parent),
    m_fileWatcher(nullptr),
    m_localSocket(nullptr),
    m_device(nullptr)
{
}

void LiveSensorDataReader::setDevice(QIODevice *device)
{
    m_device = device;
}

void LiveSensorDataReader::read()
{
    if (qobject_cast<QFile*>(m_device))
    {
        SensorDataReader::read();
    }

    if (qobject_cast<QTcpSocket*>(m_device))
    {

    }

    if (qobject_cast<QLocalSocket*>(m_device))
    {

    }
}

void LiveSensorDataReader::setFile(const QString &path)
{
    SensorDataReader::setFile(path);
    m_fileWatcher->addPath(path);
}
