/***************************************************************************
File		: SensorDataReader.cpp
Project		: AdvBoard
Description	: Class for reading sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/SensorDataReader.h"

#include <QTimer>
#include <QVector>
#include <QFileSystemWatcher>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>

SensorDataReader::SensorDataReader(QObject* parent) : QObject(parent),
    m_file(nullptr),
    m_readTimer(new QTimer(this)),
    m_interval(100),
    m_dataSnapshotCount(0),
    m_dataIndex(0)
{
}

int SensorDataReader::dataSnapshotCount() const
{
    return m_dataSnapshotCount;
}

void SensorDataReader::startReading()
{
    if (m_readTimer)
        m_readTimer->start(m_interval);
    qDebug() << "start reading: " << m_interval;
}

void SensorDataReader::readSnapshot()
{
    QVector<QVariant> dataToSend;
    dataToSend.reserve(m_sensorCount);

    if (m_dataIndex < m_data.size())
    {
        QJsonArray data = m_data[m_dataIndex++];
        for (int i = 0; i < data.size(); ++i)
        {
            dataToSend.push_back(data[i].toVariant());
        }
        emit dataRead(dataToSend);
    }
}

void SensorDataReader::read()
{
    QByteArray filedata = m_file->readAll();
    QJsonParseError parseError;
    QJsonDocument sensorDocument = QJsonDocument::fromJson(filedata, &parseError);

    if (sensorDocument.isNull())
    {
        emit dataInvalid(parseError.errorString());
    }
    else
    {
        QJsonObject sensorDataObject = sensorDocument.object();
        QJsonArray data = sensorDataObject["sensorData"].toArray();
        m_dataSnapshotCount = data.size();

        for (int i = 0; i < m_dataSnapshotCount; ++i)
        {
            m_data.push_back(data[i].toArray());
        }

        m_interval = sensorDataObject["interval"].toInt();

        const int dashboardType = sensorDataObject["dashboardType"].toInt();

        QJsonArray sensorArray = sensorDataObject["sensors"].toArray();

        const int sensorCount = sensorArray.size();
        QVector<QJsonObject> sensors;
        sensors.reserve(sensorCount);

        for (int i = 0; i < sensorCount; ++i)
        {
            sensors.push_back(sensorArray[i].toObject());
        }

        connect(m_readTimer, &QTimer::timeout, this, &SensorDataReader::readSnapshot);

        emit initDashBoard(dashboardType);
        emit initSensors(sensors);
    }
}

void SensorDataReader::setFile(const QString &path)
{
    m_path = path;
    m_file = new QFile(m_path);
    if (m_file->open(QFile::ReadOnly))
    {
        qDebug() << "reading";
        read();
    }
    else
    {
        emit dataInvalid(QLatin1String("File cannot be opened!"));
    }
}
