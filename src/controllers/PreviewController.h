#ifndef PREVIEWCONTROLLER_H
#define PREVIEWCONTROLLER_H
#include "src/widgets/PreviewWidget.h"
#include "src/VideoRecorder.h"


#include <QObject>
#include <QTimer>

class PreviewController : public QObject
{
    Q_OBJECT
public:
    explicit PreviewController(QObject *parent = nullptr);
	~PreviewController();
    void setView(PreviewWidget* const view);
	void setAdvScene(AdvVideoScene* const scene, const VideoRecorder::VideoWriterConstructData& data);
    PreviewWidget* const view() const;
private:

    PreviewWidget* m_view;
	AdvVideoScene* m_scene;
	VideoRecorder* m_videoRecorder;
	VideoRecorder::VideoWriterConstructData m_videoRecorderConstructData;

	QTimer* m_writeFrameTimer;

private slots:
	void sendFrameToWriter();
};

#endif // PREVIEWCONTROLLER_H
