/***************************************************************************
File		: MotorcylceDashboard.h
Project		: AdvBoard
Description	: MotorcycleDashboard dashboard
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef MOTORCYCLEDASHBOARD_H
#define MOTORCYCLEDASHBOARD_H

#include "src/dashboards/AbstractDashboard.h"

class MotorcycleDashboard : public AbstractDashboard
{
public:
    MotorcycleDashboard();
    void addSensor(AdvSensorItem* sensor);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QRectF boundingRect() const;

};

#endif // MOTORCYCLEDASHBOARD_H
