#include "src/dashboards/AbstractDashboard.h"

#include <QGraphicsObject>

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

void AbstractDashboard::updateSensors(const QVector<QVariant>& values)
{
    int idx = 0;
    for(auto* sensor : m_advSensorItems)
    {
        emit sensor->updateSensor(values[idx++]);
    }
}
