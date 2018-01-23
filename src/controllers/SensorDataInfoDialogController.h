/***************************************************************************
File		: SensorDataInfoDialogController.h
Project		: AdvBoard
Description	: Controller class for SensorDataInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORDATAINFODIALOGCONTROLLER_H
#define SENSORDATAINFODIALOGCONTROLLER_H

#include <QObject>

class SensorDataInfoDialogController : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataInfoDialogController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENSORDATAINFODIALOGCONTROLLER_H
