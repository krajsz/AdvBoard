/***************************************************************************
File		: AbstractDashboard.h
Project		: AdvBoard
Description	: Base class of dashboards
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ABSTRACTDASHBOARD_H
#define ABSTRACTDASHBOARD_H

#include "src/datasources/SensorDataReader.h"
#include "src/view/AdvSensorItem.h"

#include <QVector>
#include <QGraphicsObject>
#include <QJsonObject>

class AbstractDashboard : public QGraphicsObject
{
    Q_OBJECT
public:
    enum class DashboardType {
        Abstract = 0,
        MotorcycleDashboard,
        BikerDashboard,
        HikerDashboard
    };

    QVector<AdvSensorItem*> sensorItems() const;
    explicit AbstractDashboard(const DashboardType dashboardType = DashboardType::Abstract, QGraphicsObject* parent = nullptr);
    DashboardType dashboardType() const;
    int numberOfSensors() const;
    QRectF boundingRect() const;
signals:
    void sensorsInitialised();
    void sensorsUpdated();
public slots:
    void initSensors(const QVector<QJsonObject>& sensorInfoData, const int animationInterval);
    void updateSensors(const QVector<QJsonValue> &values);
    virtual void layoutSensors();

protected:
    DashboardType m_type;
    QVector<AdvSensorItem*> m_advSensorItems;

};

#endif // ABSTRACTDASHBOARD_H
