#ifndef ADVBOARDMAIN_H
#define ADVBOARDMAIN_H

#include <QMainWindow>
#include "src/controllers/AdvMainController.h"
#include "src/dialogs/SensorDataInfoDialog.h"
#include "src/dialogs/VideoInfoDialog.h"
#include "src/dialogs/SensorDataValidatingDialog.h"
#include "src/dialogs/SettingDialog.h"
#include "src/view/AdvVideoView.h"
#include "src/dialogs/VideoLoadingDialog.h"

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

private:
    Ui::AdvBoardMain *ui;
    AdvMainController* m_controller;

    AdvVideoView* m_view;
    VideoInfoDialog* m_videoInfoDialog;
    SensorDataInfoDialog* m_sensorDataInfoDialog;

};

#endif // ADVBOARDMAIN_H
