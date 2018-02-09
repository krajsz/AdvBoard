#ifndef ADVBOARDMAIN_H
#define ADVBOARDMAIN_H

#include "src/controllers/AdvMainController.h"

#include "src/widgets/DashboardSetupWidget.h"
#include "src/widgets/LiveProcessingSetupWidget.h"
#include "src/widgets/PostProcessingSetupWidget.h"
#include "src/widgets/PreviewWidget.h"
#include "src/widgets/SensorDataValidationErrorsDialog.h"
#include "src/widgets/SelectProcessingModeWidget.h"

#include <QMainWindow>
#include <QStackedWidget>

class QKeyEvent;
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

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

    void nextWidget();
    void previousWidget();

    void closeApp();

    void about();
private:
    Ui::AdvBoardMain *ui;
    AdvMainController* m_controller;

    DashboardSetupWidget* m_dashboardSetupWidget;
    LiveProcessingSetupWidget* m_liveProcessingWidget;
    PostProcessingSetupWidget* m_postProcessingWidget;
    PreviewWidget* m_previewWidget;
    SelectProcessingModeWidget* m_selectProcessingModeWidget;

    QStackedWidget* m_stackedWidget;
};

#endif // ADVBOARDMAIN_H
