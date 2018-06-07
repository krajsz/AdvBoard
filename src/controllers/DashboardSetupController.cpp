#include "src/controllers/DashboardSetupController.h"
#include "src/controllers/AdvViewController.h"
#include "src/widgets/DashboardSetupWidget.h"

#include "src/datasources/SensorDataReader.h"
#include <QDebug>

DashboardSetupController::DashboardSetupController(QObject *parent) : QObject(parent),
	m_viewController(new AdvViewController)
{
}

void DashboardSetupController::setView(DashboardSetupWidget * const view)
{
	m_view = view;
	m_viewController->setView(m_view->advView());
}

DashboardSetupWidget * const DashboardSetupController::view() const
{
	return m_view;
}

void DashboardSetupController::startProcessing()
{
	if (m_sensorDataReader)
	{
		qDebug() << "sdr start";
		m_sensorDataReader->startReading();
	}

	if (m_viewController)
	{
		qDebug() << "dsc play";
		m_viewController->play();
	}
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
}

