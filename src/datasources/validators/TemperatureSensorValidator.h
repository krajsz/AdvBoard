/***************************************************************************
File		: TemperatureSensorValidator.h
Project		: AdvBoard
Description	: Class for validating a temperature sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef TEMPERATURESENSORVALIDATOR_H
#define TEMPERATURESENSORVALIDATOR_H

#include <QObject>

class TemperatureSensorValidator : public QObject
{
    Q_OBJECT
public:
    explicit TemperatureSensorValidator(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TEMPERATURESENSORVALIDATOR_H
