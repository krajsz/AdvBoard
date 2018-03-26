/***************************************************************************
File		: AdvViewController.h
Project		: AdvBoard
Description	: Controller class for AdvVideoView
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ADVVIEWCONTROLLER_H
#define ADVVIEWCONTROLLER_H

#include "src/datasources/SensorDataReader.h"
#include <QObject>
#include <QJsonValue>

class AdvVideoView;
class AdvViewController : public QObject
{
    Q_OBJECT
public:
    explicit AdvViewController(QObject *parent = nullptr);
    void setView(AdvVideoView* const view);
    AdvVideoView * const view() const;

signals:
    void setVideo(const QUrl& url);
    void play();

    void update();
    void dataReadSignal(const QVector<QJsonValue>& data);
    void initSensorsSignal(const QVector<QJsonObject>& sensordata, const int animationInterval);
    void initDashboardSignal(int dashboardType);
public slots:
    void dataRead(const QVector<QJsonValue> &data);
    void initSensors(const QVector<QJsonObject>& sensordata, const int animationInterval);
    void initDashboard(int dashboardType);
private:
    AdvVideoView* m_view;

};

#endif // ADVVIEWCONTROLLER_H
