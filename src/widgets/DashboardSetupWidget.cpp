/***************************************************************************
File		: DashboardSetupWidget.cpp
Project		: AdvBoard
Description	: Dashboard setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/widgets/DashboardSetupWidget.h"
#include "src/view/AdvVideoView.h"

#include "ui_dashboardsetupwidget.h"
/***************************************************************************/
#include <QDebug>

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

void DashboardSetupWidget::resetPointers()
{
	m_view = nullptr;
	ui->dashboardSetupGraphicsView = nullptr;
	qDebug() << "resetPtr";
}

AdvVideoView* DashboardSetupWidget::advView() const
{
	return m_view;
}

void DashboardSetupWidget::setDashboardType(int dashboardType)
{
    ui->dashboardTypeComboBox->setCurrentIndex(dashboardType - 1);
}
