#ifndef LIVEPROCESSINGSETUPCONTROLLER_H
#define LIVEPROCESSINGSETUPCONTROLLER_H

#include <QObject>

class LiveProcessingSetupController : public QObject
{
    Q_OBJECT
public:
    explicit LiveProcessingSetupController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LIVEPROCESSINGSETUPCONTROLLER_H