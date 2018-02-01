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

void AbstractDashboard::updateSensors(const QVector<QJsonValue>& values)
{
    Q_ASSERT(values.size() == m_advSensorItems.size());

    for (int i = 0; i < m_advSensorItems.size(); ++i)
    {
        QJsonValue val = values[i];

        if(val.isArray())
        {
            const QJsonArray& arr = val.toArray();
            Q_ASSERT(arr.size() == 2);

            QPointF value;
            value.setX(arr[0].toDouble());
            value.setY(arr[1].toDouble());
            emit m_advSensorItems[i]->updateSensor(QVariant(value));
        }
        else
        {
            emit m_advSensorItems[i]->updateSensor(values[i].toVariant());
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
        if (!min.isUndefined())
        {
            minVal = min.toVariant();
        }

        const QJsonValue& max = sensorData["max"];
        QVariant maxVal;
        if (!max.isUndefined())
        {
            maxVal = max.toVariant();
        }

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
