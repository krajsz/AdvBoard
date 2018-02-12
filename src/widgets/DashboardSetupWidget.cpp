/***************************************************************************
File		: DashboardSetupWidget.cpp
Project		: AdvBoard
Description	: Dashboard setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src\widgets\DashboardSetupWidget.h"
#include "ui_dashboardsetupwidget.h"

DashboardSetupWidget::DashboardSetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DashboardSetupWidget)
{
    ui->setupUi(this);

    m_view = ui->dashboardSetupGraphicsView;
    m_view->show();
}

DashboardSetupWidget::~DashboardSetupWidget()
{
    delete ui;
}

void DashboardSetupWidget::setController(DashboardSetupController *controller)
{
    m_controller = controller;
    m_view->setController(m_controller->viewController());

    connect(m_controller, &DashboardSetupController::selectDashboardType, this, &DashboardSetupWidget::setDashboardType);
}

void DashboardSetupWidget::setDashboardType(int dashboardType)
{
    ui->dashboardTypeComboBox->setCurrentIndex(dashboardType - 1);
}


