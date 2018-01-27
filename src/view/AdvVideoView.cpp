#include "src/view/AdvVideoView.h"
#include "src/datasources/VideoSource.h"
#include "src/controllers/AdvViewController.h"

#include <QDebug>
AdvVideoView::AdvVideoView(QWidget *parent) : QGraphicsView(parent),
    m_advScene(nullptr)
{
}

void AdvVideoView::setController(AdvViewController* controller)
{
    m_controller = controller;
}

void AdvVideoView::setScenee(AdvVideoScene *scene)
{
    m_advScene = scene;

    connect(m_controller, &AdvViewController::setVideo, m_advScene->video(), &VideoSource::setVideo);
    connect(m_controller, &AdvViewController::play, m_advScene->video(), &VideoSource::play);
    setScene(m_advScene);
    m_advScene->setup();
    qDebug() << this->scene();
    qDebug() << "screct: " << this->sceneRect();
    qDebug() << "scene item" << scene->items().size();

}
