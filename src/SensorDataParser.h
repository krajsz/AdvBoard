#ifndef SENSORDATAPARSER_H
#define SENSORDATAPARSER_H

#include "SensorData.h"

#include <QObject>
#include <QJsonDocument>

class SensorDataParser : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataParser(QObject *parent = nullptr, const SensorData& data);
    QVector<AbstractSensor*> parse() const;

signals:

public slots:
};

#endif // SENSORDATAPARSER_H
