/***************************************************************************
File		: SensorDataReader.cpp
Project		: AdvBoard
Description	: Class for reading sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/SensorDataReader.h"
#include "src/sensors/AccelerationSensor.h"
#include "src/sensors/GPSpositionSensor.h"
#include "src/sensors/HumiditySensor.h"
#include "src/sensors/SpeedSensor.h"
#include "src/sensors/TemperatureSensor.h"

/***************************************************************************/
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
    m_dataIndex(0),
    m_sensorDataSourceValidator(new SensorDataSourceValidator(this))
{
}

SensorDataReader::~SensorDataReader()
{
    delete m_sensorDataSourceValidator;
}
int SensorDataReader::dataSnapshotCount() const
{
    return m_dataSnapshotCount;
}

int SensorDataReader::dashboardType() const
{
    return m_dashboardType;
}

int SensorDataReader::interval() const
{
    return m_interval;
}

QVector<QJsonObject> SensorDataReader::sensorData() const
{
    return m_sensorData;
}

void SensorDataReader::startReading()
{
    if (m_readTimer)
        m_readTimer->start(m_interval);
}

void SensorDataReader::readSnapshotSlot()
{
    readSnapshot(m_dataIndex);
    m_dataIndex++;
}

void SensorDataReader::readSnapshot(const int idx)
{
    QVector<QJsonValue> dataToSend;
    dataToSend.reserve(m_sensorCount);

    if (idx < m_data.size())
    {
        QJsonArray data = m_data[idx];
        for (int i = 0; i < data.size(); ++i)
        {
            dataToSend.push_back(data[i]);
        }
        emit dataRead(dataToSend);
    }
}

void SensorDataReader::read(bool init)
{
    if (!m_file->isOpen())
        if (!m_file->open(QFile::ReadOnly))
        {
            emit dataInvalid(QLatin1String("File cannot be opened!"));
            return;
        }
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

        if (!m_data.empty())
        {
            m_data.clear();
        }

        m_dataSnapshotCount = data.size();

        m_data.reserve(m_dataSnapshotCount);
        for (int i = 0; i < m_dataSnapshotCount; ++i)
        {
            m_data.push_back(data[i].toArray());
        }

        if (init)
        {
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

            connect(m_readTimer, &QTimer::timeout, this, &SensorDataReader::readSnapshotSlot);

            bool bothValid = true;
            if (m_sensorDataSourceValidator->validateDashboard(dashboardType))
            {
                qDebug() << "initdashboard";
                //emit initDashBoard(dashboardType);
                m_dashboardType = dashboardType;
            }
            else
            {
                bothValid = false;
            }

            if (m_sensorDataSourceValidator->validateSensors(sensors))
            {
                qDebug() << "initsensors";
                //emit initSensors(sensors, m_interval);
                m_sensorData = sensors;
            }
            else
            {
                bothValid = false;
            }

            if (bothValid)
            {
                emit sensorDataIsValid(true);
            }
            else
            {
                emit sensorDataIsValid(false);
            }
        }
    }
}

void SensorDataReader::setFile(const QString &path)
{
    m_path = path;
    m_file = new QFile(m_path);
}

AbstractSensor* SensorDataReader::sensorFromData(const QJsonObject &sensorData)
{
	const int type = sensorData["type"].toInt();
	const int id = sensorData["id"].toInt();


	qDebug() << sensorData;

	const QJsonValue& min = sensorData.value("min");
	qDebug() << "min:: " << min;
	QVariant minVal;
	const AbstractSensor::SensorType ttype = static_cast<AbstractSensor::SensorType>(type);

	qDebug() <<"ttype "  <<ttype;
	if (!min.isUndefined())
	{
		if (ttype == AbstractSensor::SensorType::GPSpositionSensor)
		{
			QPointF minpos;
			minpos.setX(min["lat"].toDouble());
			minpos.setY(min["lon"].toDouble());
			qDebug() <<"GPS "  <<ttype;

			minVal = minpos;
		}
		else if (ttype == AbstractSensor::SensorType::AccelerationSensor)
		{
			QPointF minAcc;
			minAcc.setX(min["x"].toDouble());
			minAcc.setY(min["y"].toDouble());

			qDebug() <<"ACCEL "  <<ttype;

			minVal = minAcc;
		}
		else
		{
			minVal = min.toVariant();
			qDebug() << "minval: " << minVal;
		}
	}
	else
	{
		qDebug() << "min undefined";
	}

	const QJsonValue& max = sensorData["max"];
	QVariant maxVal;
	if (!max.isUndefined())
	{
		if (ttype == AbstractSensor::SensorType::GPSpositionSensor)
		{
			QPointF maxpos;
			maxpos.setX(max["lat"].toDouble());
			maxpos.setY(max["lon"].toDouble());

			maxVal = maxpos;
		}
		else if (ttype == AbstractSensor::SensorType::AccelerationSensor)
		{
			QPointF maxAcc;
			maxAcc.setX(max["x"].toDouble());
			maxAcc.setY(max["y"].toDouble());

			maxVal = maxAcc;
		}
		else
		{
			maxVal = max.toVariant();
		}
	}

	qDebug() << minVal << " max: " << maxVal;

	AbstractSensor* sensor = nullptr;
	switch (type) {
	case AbstractSensor::SensorType::TemperatureSensor:
		sensor = new TemperatureSensor(id, minVal.toDouble(), maxVal.toDouble());
		break;
	case AbstractSensor::SensorType::AccelerationSensor:
		sensor = new AccelerationSensor(id, maxVal.toDouble(), maxVal.toDouble());
		break;
	case AbstractSensor::SensorType::GPSpositionSensor:
		sensor = new GPSpositionSensor(id);
		break;
	case AbstractSensor::SensorType::HumiditySensor:
		sensor = new HumiditySensor(id, minVal.toDouble(), maxVal.toDouble());
		break;
	case AbstractSensor::SensorType::SpeedSensor:
		sensor = new SpeedSensor(id, maxVal.toInt());
		break;
	default:
		break;
	}

	return sensor;
}

