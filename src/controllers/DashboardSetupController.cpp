#include "src/controllers/DashboardSetupController.h"
#include "src/controllers/AdvViewController.h"
#include "src/widgets/DashboardSetupWidget.h"

#include "src/datasources/SensorDataReader.h"

DashboardSetupController::DashboardSetupController(QObject *parent) : QObject(parent),
    m_viewController(new AdvViewController)
{
    /*

    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->viewController(), &AdvViewController::play);
    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->sensorDataReader(), &SensorDataReader::startReading);
*/
}

void DashboardSetupController::setView(DashboardSetupWidget * const view)
{
    m_view = view;
}

DashboardSetupWidget * const DashboardSetupController::view() const
{
    return m_view;
}

AdvViewController* DashboardSetupController::viewController()
{
    return m_viewController;
}

void DashboardSetupController::setSensorDataReader(SensorDataReader *sensorDataReader)
{
    m_sensorDataReader = sensorDataReader;

    connect(m_sensorDataReader, &SensorDataReader::dataRead, m_viewController, &AdvViewController::dataRead);

    m_viewController->initDashboard(m_sensorDataReader->dashboardType());
    m_viewController->initSensors(m_sensorDataReader->sensorData(), m_sensorDataReader->interval());

    m_view->setDashboardType(m_sensorDataReader->dashboardType());
    //emit sensorDataReader->initDashBoard(m_sensorDataReader->dashboardType());
    //emit sensorDataReader->initSensors(m_sensorDataReader->sensorData(), m_sensorDataReader->interval());
}

