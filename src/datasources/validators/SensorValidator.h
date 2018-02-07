/***************************************************************************
File		: SensorValidator.h
Project		: AdvBoard
Description	: Base class for validating a sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORVALIDATOR_H
#define SENSORVALIDATOR_H

#include <QObject>

class SensorValidator : public QObject
{
    Q_OBJECT
public:
    explicit SensorValidator(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENSORVALIDATOR_H
