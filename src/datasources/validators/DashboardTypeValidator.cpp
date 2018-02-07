/***************************************************************************
File		: DashboardValidator.cpp
Project		: AdvBoard
Description	: Class for validating a dashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/DashboardTypeValidator.h"
#include "src/dashboards/AbstractDashboard.h"

bool DashboardValidator::validate(const int type) noexcept
{
    const AbstractDashboard::DashboardType dtype = static_cast<AbstractDashboard::DashboardType>(type);
    switch (dtype)
    {
    case AbstractDashboard::DashboardType::MotorcycleDashboard:
        break;
    case AbstractDashboard::DashboardType::BikerDashboard:
        break;
    case AbstractDashboard::DashboardType::HikerDashboard:
        break;
    default:
        m_errorString = "Dashboard not valid, unkown type: "+
                           QString::number(type);
        return false;
    }
    return true;
}

QString DashboardValidator::errorString() const
{
    return m_errorString;
}
