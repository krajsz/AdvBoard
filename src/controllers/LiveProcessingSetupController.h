#ifndef LIVEPROCESSINGSETUPCONTROLLER_H
#define LIVEPROCESSINGSETUPCONTROLLER_H
#include "src/datasources/LiveSensorDataReader.h"
#include "src/widgets/LiveProcessingSetupWidget.h"
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

    void setView(LiveProcessingSetupWidget* const view);
    LiveProcessingSetupWidget* const view() const;
signals:

public slots:
private:
    Preview m_preview;
    LiveProcessingSetupWidget* m_view;
    LiveSensorDataReader::SourceType m_sourceType;
};

#endif // LIVEPROCESSINGSETUPCONTROLLER_H
