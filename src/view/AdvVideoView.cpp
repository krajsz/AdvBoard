#include "src/view/AdvVideoView.h"
#include "src/datasources/VideoSource.h"

#include <QDebug>
AdvVideoView::AdvVideoView(QWidget *parent) : QGraphicsView(parent),
    m_advScene(new AdvVideoScene)
{
    connect(m_advScene, &AdvVideoScene::sceneSetupDone, this, &AdvVideoView::setScenee);
}

/*void AdvVideoView::setController(AdvViewController* controller)
{
    m_controller = controller;
    connect(m_controller, &AdvViewController::setVideo, m_advScene->video(), &VideoSource::setVideo);
    connect(m_controller, &AdvViewController::play, m_advScene->video(), &VideoSource::play);
    connect(m_controller, &AdvViewController::initDashboardSignal, m_advScene, &AdvVideoScene::initDashboard);
    connect(m_controller, &AdvViewController::dataReadSignal, m_advScene, &AdvVideoScene::updateSensorsSignal);
    connect(m_controller, &AdvViewController::initSensorsSignal, m_advScene, &AdvVideoScene::initSensorSignal);
}*/

AdvVideoScene* AdvVideoView::videoScene() const
{
    return m_advScene;
}

void AdvVideoView::setScenee()
{
    setScene(m_advScene);
    scene()->setSceneRect(0,0, this->width(), this->height());
    m_advScene->resize(this->size());
}
