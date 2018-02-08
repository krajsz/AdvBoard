#ifndef ADVBOARDMAIN_H
#define ADVBOARDMAIN_H

#include "src/controllers/AdvMainController.h"
#include "src/widgets//SensorDataInfoDialog.h"
#include "src/widgets/VideoInfoDialog.h"
#include "src/widgets/SensorDataValidatingDialog.h"
#include "src/widgets/SettingDialog.h"
#include "src/view/AdvVideoView.h"
#include "src/widgets/VideoLoadingDialog.h"

#include "src/widgets/DashboardSetupWidget.h"
#include "src/widgets/LiveProcessingSetupWidget.h"
#include "src/widgets/PostProcessingSetupWidget.h"
#include "src/widgets/PreviewWidget.h"
#include "src/widgets/SensorDataValidationErrorsDialog.h"
#include "src/widgets/SelectProcessingModeWidget.h"

#include <QMainWindow>
#include <QStackedWidget>

namespace Ui {
class AdvBoardMain;
}

class AdvBoardMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdvBoardMain(QWidget *parent = 0);
    ~AdvBoardMain();
    void setController(AdvMainController* controller);

private slots:
    void openSensorData();

    void nextWidget();
    void previousWidget();

    void closeApp();

    void about();

    void optionsActionTriggered();

    void sensorDataInvalid(const QString& errorstring);
private:
    Ui::AdvBoardMain *ui;
    AdvMainController* m_controller;

    AdvVideoView* m_view;
    VideoInfoDialog* m_videoInfoDialog;
    SensorDataInfoDialog* m_sensorDataInfoDialog;
    DashboardSetupWidget* m_dashboardSetupWidget;
    LiveProcessingSetupWidget* m_liveProcessingWidget;
    PostProcessingSetupWidget* m_postProcessingWidget;
    PreviewWidget* m_previewWidget;
    SelectProcessingModeWidget* m_selectProcessingModeWidget;


    QStackedWidget* m_stackedWidget;
};

#endif // ADVBOARDMAIN_H
