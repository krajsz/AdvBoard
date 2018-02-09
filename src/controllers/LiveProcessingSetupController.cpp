#include "LiveProcessingSetupController.h"

LiveProcessingSetupController::LiveProcessingSetupController(QObject *parent) : QObject(parent)
{

}

void LiveProcessingSetupController::setPreview(const LiveProcessingSetupController::Preview preview)
{
    m_preview = preview;
}
