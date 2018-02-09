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
#include "src/controllers/DashboardSetupController"

class AdvMainController : public QObject
{
    Q_OBJECT
public:
    explicit AdvMainController(QObject* parent = nullptr);
    ~AdvMainController();

    PostProcessingSetupController* postProcessingSetupController();
    LiveProcessingSetupController* liveProcessingSetupController();
    DashboardSetupController* dashboardSetupController();
    PreviewController* previewController();

private:

    PostProcessingSetupController* m_postProcessingSetupController;
    LiveProcessingSetupController* m_liveProcessingSetupController;
    DashboardSetupController* m_dashboardSetupController;
    PreviewController* m_previewController;
};

#endif // ADVMAINCONTROLLER_H
