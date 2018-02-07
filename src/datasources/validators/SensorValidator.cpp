/***************************************************************************
File		: SensorValidator.cpp
Project		: AdvBoard
Description	: Base class for validating a sensor
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/datasources/validators/SensorValidator.h"

QString SensorValidator::errorString() const
{
    return m_errorString;
}
