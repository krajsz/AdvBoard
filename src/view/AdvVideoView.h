#ifndef ADVVIDEOVIEW_H
#define ADVVIDEOVIEW_H

#include "src/view/AdvVideoScene.h"

#include <QGraphicsView>

class AdvVideoView final : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AdvVideoView(QWidget *parent = nullptr);
    AdvVideoScene* videoScene();

signals:

public slots:
private slots:
    void setScenee();
private:
    AdvVideoScene* m_advScene;
};

#endif // ADVVIDEOVIEW_H
