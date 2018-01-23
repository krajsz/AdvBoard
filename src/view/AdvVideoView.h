#ifndef ADVVIDEOVIEW_H
#define ADVVIDEOVIEW_H

#include "AdvVideoScene.h"

#include <QObject>

class AdvVideoView : public QObject
{
    Q_OBJECT
public:
    explicit AdvVideoView(QObject *parent = nullptr);

signals:

public slots:
private:
    AdvVideoScene* m_advScene;
};

#endif // ADVVIDEOVIEW_H
