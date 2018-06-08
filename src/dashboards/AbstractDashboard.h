/***************************************************************************
File		: AbstractDashboard.h
Project		: AdvBoard
Description	: Base class of dashboards
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ABSTRACTDASHBOARD_H
#define ABSTRACTDASHBOARD_H

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
	explicit AbstractDashboard(const DashboardType dashboardType = DashboardType::Abstract, QGraphicsObject* parent = nullptr);

    QVector<AdvSensorItem*> sensorItems() const;
    AbstractSensor* sensorWithId(const int id) const;
    DashboardType dashboardType() const;
    int numberOfSensors() const;
    QRectF boundingRect() const;

	void setAllowDraggin(bool allow);
	bool allowDragging() const;

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
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void updateSensorWithID(const int id, const QJsonValue& value);

	bool m_allowDragging;
	bool m_dragging;
};

#endif // ABSTRACTDASHBOARD_H
