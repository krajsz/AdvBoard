#ifndef ADVVIDEOVIEW_H
#define ADVVIDEOVIEW_H

#include "src/view/AdvVideoScene.h"
#include "src/controllers/AdvViewController.h"

#include <QGraphicsView>

class AdvVideoView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AdvVideoView(QWidget *parent = nullptr);
    void setController(AdvViewController* controller);
    AdvVideoScene* videoScene();
signals:

public slots:
private slots:
    void setScenee();
    void repaintt();
private:
    AdvVideoScene* m_advScene;
    AdvViewController* m_controller;
};

#endif // ADVVIDEOVIEW_H
