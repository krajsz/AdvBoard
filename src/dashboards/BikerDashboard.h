/***************************************************************************
File		: BikerDashboard.h
Project		: AdvBoard
Description	: BikerDashboard dashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef BIKERDASHBOARD_H
#define BIKERDASHBOARD_H

#include "src/dashboards/AbstractDashboard.h"

class BikerDashboard : public AbstractDashboard
{
public:
    BikerDashboard();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

public slots:
    void layoutSensors();

};

#endif // BIKERDASHBOARD_H
