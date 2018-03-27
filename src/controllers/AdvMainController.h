/***************************************************************************
File		: AdvMainController.h
Project		: AdvBoard
Description	: Main controller class
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef ADVMAINCONTROLLER_H
#define ADVMAINCONTROLLER_H

#include <QObject>
#include "src/controllers/AdvViewController.h"
#include "src/controllers/PostProcessingSetupController.h"
#include "src/controllers/LiveProcessingSetupController.h"
#include "src/controllers/PreviewController.h"
#include "src/controllers/DashboardSetupController.h"
#include "src/widgets/SelectProcessingModeWidget.h"

#include "src/AdvBoardMain.h"
class AdvMainController : public QObject
{
    Q_OBJECT
public:
    explicit AdvMainController(QObject* parent = nullptr);
    ~AdvMainController();

    void setView(AdvBoardMain* const view);
    AdvBoardMain * const view() const;

    PostProcessingSetupController* postProcessingSetupController();
    LiveProcessingSetupController* liveProcessingSetupController();
    DashboardSetupController* dashboardSetupController();
    PreviewController* previewController();

private slots:
    void dashboardSetupShown(const SelectProcessingModeWidget::ProcessingMode mode);
    void liveProcessingSetupShown();
    void postProcessingSetupShown();
    void previewShown();
private:
    PostProcessingSetupController* m_postProcessingSetupController;
    LiveProcessingSetupController* m_liveProcessingSetupController;
    DashboardSetupController* m_dashboardSetupController;
    PreviewController* m_previewController;

    AdvBoardMain* m_view;

    void connectView();
};

#endif // ADVMAINCONTROLLER_H
