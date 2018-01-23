/***************************************************************************
File		: LiveSensorDataReader.cpp
Project		: AdvBoard
Description	: Class for reading live sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef LIVESENSORDATAREADER_H
#define LIVESENSORDATAREADER_H

#include "SensorDataReader.h"

class LiveSensorDataReader : public SensorDataReader
{
public:
    LiveSensorDataReader();
    void read();

};

#endif // LIVESENSORDATAREADER_H
