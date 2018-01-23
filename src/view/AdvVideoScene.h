#ifndef ADVVIDEOSCENE_H
#define ADVVIDEOSCENE_H


#include "AbstractDashboard.h"
#include "VideoSource.h"

#include <QObject>
#include <QGraphicsScene>

class AdvVideoScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AdvVideoScene(QGraphicsScene *parent = nullptr);

signals:

public slots:
private:
    AbstractDashboard* m_dashBoard;
    VideoSource* m_video;

};

#endif // ADVVIDEOSCENE_H
