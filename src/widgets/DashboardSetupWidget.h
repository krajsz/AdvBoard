/***************************************************************************
File		: DashboardSetupWidget.h
Project		: AdvBoard
Description	: Dashboard setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef DASHBOARDSETUPWIDGET_H
#define DASHBOARDSETUPWIDGET_H

#include "src/view/AdvVideoView.h"
#include "src/controllers/DashboardSetupController"

#include <QWidget>

namespace Ui {
class DashboardSetupWidget;
}

class DashboardSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardSetupWidget(QWidget *parent = 0);
    ~DashboardSetupWidget();

    void setController(DashboardSetupController* controller);
private:
    Ui::DashboardSetupWidget *ui;
    AdvVideoView* m_view;

    DashboardSetupController* m_controller;

private slots:
    void setDashboardType(int dashboardType);
};

#endif // DASHBOARDSETUPWIDGET_H
