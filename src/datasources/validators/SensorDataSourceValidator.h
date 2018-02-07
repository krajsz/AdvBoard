/***************************************************************************
File		: SensorDataSourceValidator.h
Project		: AdvBoard
Description	: Class for validating a sensor data source
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef VALIDATORSSENSORDATASOURCEVALIDATOR_H
#define VALIDATORSSENSORDATASOURCEVALIDATOR_H

#include <QObject>

class SensorDataSourceValidator : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataSourceValidator(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VALIDATORSSENSORDATASOURCEVALIDATOR_H
