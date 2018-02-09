#ifndef LIVEPROCESSINGSETUPCONTROLLER_H
#define LIVEPROCESSINGSETUPCONTROLLER_H
#include "src/datasources/LiveSensorDataReader.h"

#include <QObject>

class LiveProcessingSetupController : public QObject
{
    Q_OBJECT
public:
    explicit LiveProcessingSetupController(QObject *parent = nullptr);
    enum Preview {
        Normal = 0,
        Fullscreen
    };
    void setPreview(const Preview preview);
signals:

public slots:
private:
    Preview m_preview;
    LiveSensorDataReader::SourceType m_sourceType;
};

#endif // LIVEPROCESSINGSETUPCONTROLLER_H
