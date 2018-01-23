#include "AdvMainController.h"

AdvMainController::AdvMainController(QObject* parent) : QObject(parent), m_mainWindow(new AdvBoardMain),
    m_sensorDataInfoDialogController(new SensorDataInfoDialogController),
    m_sensorDataValidatingDialogController(new SensorDataValidatingDialogController),
    m_videoInfoDialogController(new VideoInfoDialogController)
{

}
