/***************************************************************************
File		: DashboardValidator.h
Project		: AdvBoard
Description	: Class for validating a dashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef DASHBOARDVALIDATOR_H
#define DASHBOARDVALIDATOR_H

#include <QString>

class DashboardValidator
{
public:
    DashboardValidator() = default;

    bool validate(const int type) noexcept;
    QString errorString() const;
private:
    QString m_errorString;

};

#endif // DASHBOARDVALIDATOR_H
