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

class DashboardSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardSetupWidget(QWidget *parent = 0);
    ~DashboardSetupWidget();

private:
    Ui::DashboardSetupWidget *ui;
};

#endif // DASHBOARDSETUPWIDGET_H
