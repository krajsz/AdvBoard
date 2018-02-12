/***************************************************************************
File		: AdvMainController.cpp
Project		: AdvBoard
Description	: Main controller class
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "AdvMainController.h"
#include "src/widgets/SelectProcessingModeWidget.h"

AdvMainController::AdvMainController(QObject* parent) : QObject(parent),
    m_previewController(nullptr),
    m_dashboardSetupController(nullptr),
    m_postProcessingSetupController(nullptr),
    m_liveProcessingSetupController(nullptr)
{
}

void AdvMainController::dashboardSetupShown(const SelectProcessingModeWidget::ProcessingMode mode)
{
    if (mode == SelectProcessingModeWidget::ProcessingMode::PostProcessing)
    {
        dashboardSetupController()->setSensorDataReader(m_postProcessingSetupController->sensorDataReader());
    }
    else if (mode == SelectProcessingModeWidget::ProcessingMode::LiveProcessing)
    {

    }
    else
    {
        //wot
    }
}

PostProcessingSetupController* AdvMainController::postProcessingSetupController()
{
    if (m_postProcessingSetupController == nullptr)
    {
        m_postProcessingSetupController = new PostProcessingSetupController;
    }
    return m_postProcessingSetupController;
}

LiveProcessingSetupController* AdvMainController::liveProcessingSetupController()
{
    if (m_liveProcessingSetupController == nullptr)
    {
        m_liveProcessingSetupController = new LiveProcessingSetupController;
    }
    return m_liveProcessingSetupController;
}
DashboardSetupController* AdvMainController::dashboardSetupController()
{
    if (m_dashboardSetupController == nullptr)
    {
        m_dashboardSetupController = new DashboardSetupController;
    }
    return m_dashboardSetupController;
}

PreviewController* AdvMainController::previewController()
{
    if (m_previewController == nullptr)
    {
        m_previewController = new PreviewController;
    }
    return m_previewController;
}


AdvMainController::~AdvMainController()
{
    if (m_previewController)
    {
        delete m_previewController;
    }
    if (m_postProcessingSetupController)
    {
        delete m_postProcessingSetupController;
    }
    if (m_liveProcessingSetupController)
    {
        delete m_liveProcessingSetupController;
    }
    if (m_dashboardSetupController)
    {
        delete m_dashboardSetupController;
    }
}


