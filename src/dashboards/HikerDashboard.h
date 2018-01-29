/***************************************************************************
File		: HikerDashboard.h
Project		: AdvBoard
Description	: HikerDashboard dashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef HIKERDASHBOARD_H
#define HIKERDASHBOARD_H

#include "src/dashboards/AbstractDashboard.h"

class HikerDashboard : public AbstractDashboard
{
public:
    HikerDashboard();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

public slots:
    void layoutSensors();

};

#endif // HIKERDASHBOARD_H
