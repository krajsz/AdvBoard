#include "DashboardSetupController"

DashboardSetupController::DashboardSetupController(QObject *parent) : QObject(parent),
    m_viewController(new AdvViewController)
{
    /*

    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->viewController(), &AdvViewController::play);
    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->sensorDataReader(), &SensorDataReader::startReading);
*/
}

AdvViewController* DashboardSetupController::viewController()
{
    return m_viewController;
}

void DashboardSetupController::setSensorDataReader(SensorDataReader *sensorDataReader)
{
    m_sensorDataReader = sensorDataReader;

    connect(m_sensorDataReader, &SensorDataReader::initDashBoard, m_viewController, &AdvViewController::initDashboard);
    connect(m_sensorDataReader, &SensorDataReader::initSensors, m_viewController, &AdvViewController::initSensors);
    connect(m_sensorDataReader, &SensorDataReader::dataRead, m_viewController, &AdvViewController::dataRead);

    emit sensorDataReader->initDashBoard(m_sensorDataReader->dashboardType());

    emit selectDashboardType(m_sensorDataReader->dashboardType());

    emit sensorDataReader->initSensors(m_sensorDataReader->sensorData(), m_sensorDataReader->interval());
}

