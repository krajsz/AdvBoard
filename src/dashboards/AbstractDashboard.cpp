/***************************************************************************
File		: AbstractDashboard.cpp
Project		: AdvBoard
Description	: Base class of the dashboards
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/dashboards/AbstractDashboard.h"

#include <QGraphicsObject>
#include <QPropertyAnimation>

#include <QDebug>

#define DASHBOARD_SENSORITEMS_PADDING 15

AbstractDashboard::AbstractDashboard(const DashboardType dashboardType, QGraphicsObject *parent) : QGraphicsObject(parent),
    m_type(dashboardType)
{
}

AbstractDashboard::DashboardType AbstractDashboard::dashboardType() const
{
    return m_type;
}

AbstractSensor* AbstractDashboard::sensorWithId(const int id) const
{
    for (const AdvSensorItem* item : m_advSensorItems)
    {
        if (item->sensor()->id() == id)
        {
            return item->sensor();
        }
    }
    return nullptr;
}

QVector<AdvSensorItem*> AbstractDashboard::sensorItems() const
{
    return m_advSensorItems;
}

int AbstractDashboard::numberOfSensors() const
{
    return m_advSensorItems.size();
}

QRectF AbstractDashboard::boundingRect() const
{
    QRectF brect;
    brect.setLeft(0);
    brect.setTop(0);
    int width = 0;
    int maxHeight = 0;

    for (const AdvSensorItem* const item : sensorItems())
    {
        if (const_cast<AdvSensorItem*>(item)->sensor()->drawingPosition() == AbstractSensor::DrawingPosition::Separate)
            width += item->boundingRect().width() + DASHBOARD_SENSORITEMS_PADDING;
        if (item->boundingRect().height() > maxHeight)
            maxHeight = item->boundingRect().height();
    }

    brect.setWidth(width);
    brect.setHeight(maxHeight + DASHBOARD_SENSORITEMS_PADDING);
    return brect;
}

void AbstractDashboard::updateSensorWithID(const int id, const QJsonValue &value)
{
    for(AdvSensorItem* sensorItem : m_advSensorItems)
    {
        if (sensorItem->sensor()->id() == id)
        {
            if(value.isArray())
            {
                Q_ASSERT(sensorItem->sensor()->value().type() == QVariant::PointF);
                const QJsonArray& arr = value.toArray();
                Q_ASSERT(arr.size() == 2);

                QPointF pointValue;
                pointValue.setX(arr[0].toDouble());
                pointValue.setY(arr[1].toDouble());
                emit sensorItem->updateSensor(QVariant(pointValue));
            }
            else
            {
                emit sensorItem->updateSensor(value.toVariant());
            }
            break;
        }
    }
}

void AbstractDashboard::updateSensors(const QVector<QJsonValue>& values)
{
    Q_ASSERT(values.size() == m_advSensorItems.size());

    for (const QJsonValue& value : values)
    {
        if (value.isObject())
        {
            const QJsonObject& data = value.toObject();
            const int id = data["id"].toInt();
            const QJsonValue& value = data["value"];
            updateSensorWithID(id, value);
        }
    }
    emit sensorsUpdated();
}

void AbstractDashboard::layoutSensors()
{
}

void AbstractDashboard::initSensors(const QVector<QJsonObject> &sensorInfoData, const int animationInterval)
{
    for (int i = 0; i < sensorInfoData.size(); ++i)
    {
        const QJsonObject& sensorData = sensorInfoData.at(i);
        const int type = sensorData["type"].toInt();
        const int id = sensorData["id"].toInt();

        bool sensorExists = false;
        for (AdvSensorItem * const item : m_advSensorItems)
        {
            if (item->sensor()->id() == id)
            {
                sensorExists = true;
                break;
            }
        }

        if (sensorExists)
        {
            continue;
        }

        const QJsonValue& min = sensorData["min"];
        QVariant minVal;
        const AbstractSensor::SensorType ttype = static_cast<AbstractSensor::SensorType>(type);
        if (!min.isUndefined())
        {
            if (ttype == AbstractSensor::SensorType::GPSpositionSensor)
            {
                QPointF minpos;
                minpos.setX(min["lat"].toDouble());
                minpos.setY(min["lon"].toDouble());

                minVal = minpos;
            }
			else if (ttype == AbstractSensor::SensorType::AccelerationSensor)
            {
                QPointF minAcc;
                minAcc.setX(min["x"].toDouble());
                minAcc.setY(min["y"].toDouble());

                minVal = minAcc;
            }
            else
            {
                minVal = min.toVariant();
            }
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
		qDebug() << minVal << " maxval: " << maxVal;
        AdvSensorItem* sensor;
        if (minVal.isValid() && maxVal.isValid())
        {
            sensor = new AdvSensorItem(static_cast<AbstractSensor::SensorType>(type), id, this, maxVal, minVal);
        }
        else if (minVal.isValid())
        {
            sensor = new AdvSensorItem(static_cast<AbstractSensor::SensorType>(type), id, this, QVariant(), minVal);

        } else if (maxVal.isValid())
        {
            sensor = new AdvSensorItem(static_cast<AbstractSensor::SensorType>(type), id, this, maxVal, QVariant() );
        }
        else
        {
            sensor = new AdvSensorItem(static_cast<AbstractSensor::SensorType>(type), id, this);
        }

        connect(sensor->sensor()->animation(), &QVariantAnimation::valueChanged, this, [=](){ emit sensorsUpdated();});
        sensor->sensor()->animation()->setDuration(animationInterval);

        m_advSensorItems.push_back(sensor);
    }
    emit sensorsInitialised();
}
