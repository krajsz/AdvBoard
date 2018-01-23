#include "AbstractSensor.h"

template<class T>
AbstractSensor::AbstractSensor(const int id, const T &val, QObject *parent) : QObject(parent), m_id(id), m_value(val)
{

}

template<class T>
bool AbstractSensor<T>::operator ==(const AbstractSensor<T>& other) const
{
    return (other.m_id == this->m_id) && (other.type() == this->type());
}

template<class T>
T AbstractSensor::value() const
{
    return m_value;
}


