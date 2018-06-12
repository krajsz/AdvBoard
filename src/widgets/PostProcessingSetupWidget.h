/***************************************************************************
File		: PostProcessingSetupWidget.cpp
Project		: AdvBoard
Description	: Postprocessing setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef POSTPROCESSINGSETUPWIDGET_H
#define POSTPROCESSINGSETUPWIDGET_H
#include "src/widgets/SensorDataInfoDialog.h"
#include "src/view/AdvVideoView.h"
#include "src/VideoRecorder.h"

#include <QWidget>

namespace Ui {
class PostProcessingSetupWidget;
}

class PostProcessingSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostProcessingSetupWidget(QWidget *parent = 0);
    ~PostProcessingSetupWidget();
    void process();

    void setResolution(const QSize& resolution);
	SensorDataInfoDialog* sensorDataInfoDialog();
	VideoRecorder::VideoWriterConstructData videoWriterConstructData() const;

public slots:
    void sensorDataIsValid(bool valid, bool bready);
    void videoLoaded(bool ready);
signals:
    void viewCompleted(AdvVideoView* view);
    void ready(bool ready) const;
    void sensorDataInfoDialogButtonClickedSignal();

    void resolutionWidthChangedSignal(int value);
    void resolutionHeightChangedSignal(int value);
    void resolutionPredefinedChangedSignal(int index);
    void loadSensorDataSignal(const QLatin1String& fileName);
    void loadVideoSourceSignal(const QUrl& url);

private:
    Ui::PostProcessingSetupWidget *ui;
    SensorDataInfoDialog* m_sensorDataInfoDialog;
private slots:

    void sensorDataInfoDialogButtonClicked();

    void previewEnabledChecked(bool checked);
    void keepAspectRatioChecked(bool checked);

    void resizeChecked(bool checked);
    void sameAsSourceChecked(bool checked);

    void resizePercentageSliderValueChanged(int value);
    void resizePercentageSpinboxValueChanged(int value);

    void resolutionWidthChanged(int value);
    void resolutionHeightChanged(int value);
    void resolutionPredefinedChanged(int index);

    void videoFormatChanged(int index);
    void previewTypeChecked(bool checked);

    void loadSensorData();
    void loadVideoSource();

    void showVideoInfo();
    void showSensorInfo();

    void showSensorValidationErrors();
};

#endif // POSTPROCESSINGSETUPWIDGET_H
