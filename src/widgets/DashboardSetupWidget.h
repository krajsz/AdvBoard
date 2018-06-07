/***************************************************************************
File		: DashboardSetupWidget.h
Project		: AdvBoard
Description	: Dashboard setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef DASHBOARDSETUPWIDGET_H
#define DASHBOARDSETUPWIDGET_H

#include <QWidget>

namespace Ui {
class DashboardSetupWidget;
}
class AdvVideoView;
class DashboardSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardSetupWidget(QWidget *parent = 0);
    ~DashboardSetupWidget();
	AdvVideoView* advView() const;
	void resetPointers();
signals:
	void startProcessing();
private:
    Ui::DashboardSetupWidget *ui;
    AdvVideoView* m_view;

public slots:
    void setDashboardType(int dashboardType);
};

#endif // DASHBOARDSETUPWIDGET_H
