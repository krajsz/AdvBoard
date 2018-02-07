#ifndef ADVBOARDMAIN_H
#define ADVBOARDMAIN_H

#include <QMainWindow>
#include "src/controllers/AdvMainController.h"
#include "src/widgets//SensorDataInfoDialog.h"
#include "src/widgets/VideoInfoDialog.h"
#include "src/widgets/SensorDataValidatingDialog.h"
#include "src/widgets/SettingDialog.h"
#include "src/view/AdvVideoView.h"
#include "src/widgets/VideoLoadingDialog.h"

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
    void openVideoSource();
    void openSensorData();

    void liveProcessingChecked(bool checked);
    void liveProcessingButtonClicked();

    void videoInfoDialogButtonClicked();
    void sensorDataInfoDialogButtonClicked();

    void startProcessing();

    void closeApp();

    void about();

    void optionsActionTriggered();

    void sensorDataInvalid(const QString& errorstring);

    void dashboardValidation(bool valid);
private:
    Ui::AdvBoardMain *ui;
    AdvMainController* m_controller;

    AdvVideoView* m_view;
    VideoInfoDialog* m_videoInfoDialog;
    SensorDataInfoDialog* m_sensorDataInfoDialog;

};

#endif // ADVBOARDMAIN_H
