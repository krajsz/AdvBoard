/***************************************************************************
File		: AbstractDashboard.h
Project		: AdvBoard
Description	: Base class of dashboards
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ABSTRACTDASHBOARD_H
#define ABSTRACTDASHBOARD_H

#include "SensorData.h"
#include "AdvSensorItem.h"

#include <QObject>
#include <QVector>
#include <QGraphicsObject>

class AbstractDashboard : public QGraphicsObject
{
    Q_OBJECT
public:
    enum DashboardType {
        MotorcycleDashboard,
        BikerDashboard,
        HikerDashboard
    };
    explicit AbstractDashboard(QGraphicsObject* parent);
    DashboardType dashboardType() const;



private:

    DashboardType m_type;
    QVector<AdvSensorItem*> m_advSensorItem;
};

#endif // ABSTRACTDASHBOARD_H
