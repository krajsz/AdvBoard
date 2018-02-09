/***************************************************************************
File		: SensorDataSourceValidator.h
Project		: AdvBoard
Description	: Class for sensor data validating
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORDATASOURCEVALIDATOR_H
#define SENSORDATASOURCEVALIDATOR_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class AbstractDashboard;

class SensorDataSourceValidator : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataSourceValidator(QObject *parent = nullptr);

    bool validateSensors(const QVector<QJsonObject>& sensors);
    bool validateLiveSensorData(const QJsonArray& sensorData, AbstractDashboard * const dashboard);
    bool validateDashboard(const int type);

     QVector<QString> validationErrors() const;
public slots:
private:
    QJsonArray m_sensorDataBoundaries;
    QVector<QString> m_validationErrors;
};

#endif // SENSORDATASOURCEVALIDATOR_H
