#include "AbstractDashboard.h"

AbstractDashboard::AbstractDashboard(QGraphicsObject *parent) : QGraphicsObject(parent)
{

}

DashboardType AbstractDashboard::dashboardType() const
{
    return m_type;
}
