#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "AbstractSensor.h"

class TemperatureSensor : public AbstractSensor
{
public:
    TemperatureSensor();

private:
    double m_value;
};

#endif // TEMPERATURESENSOR_H
