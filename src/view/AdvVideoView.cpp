#include "src/view/AdvVideoView.h"
#include "src/datasources/VideoSource.h"
/***************************************************************************/
#include <QDebug>
AdvVideoView::AdvVideoView(QWidget *parent) : QGraphicsView(parent),
    m_advScene(new AdvVideoScene)
{
	setInteractive(true);
	setDragMode(QGraphicsView::NoDrag);
    connect(m_advScene, &AdvVideoScene::sceneSetupDone, this, &AdvVideoView::setScenee);
}

AdvVideoScene* AdvVideoView::videoScene() const
{
    return m_advScene;
}

void AdvVideoView::setScenee()
{
	qDebug() << "setScenee";
    setScene(m_advScene);
    scene()->setSceneRect(0,0, this->width(), this->height());
    m_advScene->resize(this->size());
}
