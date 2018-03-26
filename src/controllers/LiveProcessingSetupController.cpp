#include "LiveProcessingSetupController.h"

LiveProcessingSetupController::LiveProcessingSetupController(QObject *parent) : QObject(parent)
{

}

void LiveProcessingSetupController::setPreview(const LiveProcessingSetupController::Preview preview)
{
    m_preview = preview;
}

void LiveProcessingSetupController::setView(LiveProcessingSetupWidget * const view)
{
    m_view = view;
}

LiveProcessingSetupWidget* const LiveProcessingSetupController::view() const
{
    return m_view;
}
