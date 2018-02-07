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

class AbstractDashboard;

class SensorDataSourceValidator : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataSourceValidator(QObject *parent = nullptr);

    bool validateSensors(const QVector<QJsonObject>& sensors) const;
    bool validateLiveSensorData(const QJsonArray& sensorData, AbstractDashboard * const dashboard) const;
    bool validateDashboard(const int type) const;

signals:
    void validationError(const QString& error) const;

public slots:
private:
    QJsonArray m_sensorDataBoundaries;
};

#endif // SENSORDATASOURCEVALIDATOR_H
