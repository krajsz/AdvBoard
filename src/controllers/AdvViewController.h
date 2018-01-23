/***************************************************************************
File		: AdvViewController.h
Project		: AdvBoard
Description	: Controller class for AdvVideoView
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ADVVIEWCONTROLLER_H
#define ADVVIEWCONTROLLER_H

#include "AdvVideoView.h"
#include "SensorData.h"
#include <QObject>

class AdvViewController : public QObject
{
    Q_OBJECT
public:
    explicit AdvViewController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ADVVIEWCONTROLLER_H
