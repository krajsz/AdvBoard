/***************************************************************************
File		: HumiditySensorValidator.h
Project		: AdvBoard
Description	: Class for validating a humidity sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef HUMIDITYSENSORVALIDATOR_H
#define HUMIDITYSENSORVALIDATOR_H

#include <QObject>

class HumiditySensorValidator : public QObject
{
    Q_OBJECT
public:
    explicit HumiditySensorValidator(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HUMIDITYSENSORVALIDATOR_H
