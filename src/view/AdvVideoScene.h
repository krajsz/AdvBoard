#ifndef ADVVIDEOSCENE_H
#define ADVVIDEOSCENE_H


#include "src/dashboards/AbstractDashboard.h"
#include "src/datasources/VideoSource.h"

#include <QObject>
#include <QGraphicsScene>

class AdvVideoScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AdvVideoScene(AbstractDashboard::DashboardType dashboardType, QGraphicsScene *parent = nullptr);

    VideoSource* video();
    AbstractDashboard* dashboard();
    void setup();
signals:

public slots:
private:
    AbstractDashboard* m_dashBoard;
    VideoSource* m_video;

};

#endif // ADVVIDEOSCENE_H
