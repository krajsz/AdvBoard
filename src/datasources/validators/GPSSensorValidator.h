/***************************************************************************
File		: GPSSensorValidator.h
Project		: AdvBoard
Description	: Class for validating a gps sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef GPSSENSORVALIDATOR_H
#define GPSSENSORVALIDATOR_H

#include <QObject>

class GPSSensorValidator : public QObject
{
    Q_OBJECT
public:
    explicit GPSSensorValidator(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GPSSENSORVALIDATOR_H
