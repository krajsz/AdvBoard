#include "src/view/AdvVideoView.h"
#include "src/datasources/VideoSource.h"
#include "src/controllers/AdvViewController.h"

#include <QDebug>
AdvVideoView::AdvVideoView(QWidget *parent) : QGraphicsView(parent),
    m_advScene(new AdvVideoScene)
{
    connect(m_advScene, &AdvVideoScene::sceneSetupDone, this, &AdvVideoView::setScenee);
}

void AdvVideoView::setController(AdvViewController* controller)
{
    m_controller = controller;
    connect(m_controller, &AdvViewController::setVideo, m_advScene->video(), &VideoSource::setVideo);
    connect(m_controller, &AdvViewController::play, m_advScene->video(), &VideoSource::play);
    connect(m_controller, &AdvViewController::initDashboardSignal, m_advScene, &AdvVideoScene::initDashboard);
    connect(m_controller, &AdvViewController::dataReadSignal, m_advScene, &AdvVideoScene::updateSensorsSignal);
    connect(m_controller, &AdvViewController::initSensorsSignal, m_advScene, &AdvVideoScene::initSensorSignal);
    connect(m_controller, &AdvViewController::update, this, &AdvVideoView::repaintt);
}

void AdvVideoView::repaintt()
{
   // scene()->update();
}

AdvVideoScene* AdvVideoView::videoScene()
{
    return m_advScene;
}

void AdvVideoView::setScenee()
{
    setScene(m_advScene);
}
