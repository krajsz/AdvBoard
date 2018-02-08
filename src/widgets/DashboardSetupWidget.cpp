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
}

DashboardSetupWidget::~DashboardSetupWidget()
{
    delete ui;
}
