#ifndef ADVVIDEOSCENE_H
#define ADVVIDEOSCENE_H


#include "src/dashboards/AbstractDashboard.h"
#include "src/datasources/VideoSource.h"

#include <QObject>
#include <QGraphicsScene>

class QSize;
class AdvVideoScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AdvVideoScene(QGraphicsScene *parent = nullptr);

    VideoSource* video();
    AbstractDashboard* dashboard();

    void resize(const QSize& size);

signals:
    void updateSensorsSignal(const QVector<QJsonValue>& data);
    void initSensorSignal(const QVector<QJsonObject> &sensordata, const int interval);

    void sceneSetupDone();
public slots:
    void initDashboard(int type);
private:
    AbstractDashboard* m_dashBoard;
    VideoSource* m_video;
private slots:
    void setup();
    void sensorsUpdated();

};

#endif // ADVVIDEOSCENE_H
