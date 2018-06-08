/***************************************************************************
File		: SensorDataInfoDialogController.cpp
Project		: AdvBoard
Description	: Controller class of SensorDataInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "SensorDataInfoDialogController.h"

SensorDataInfoDialogController::SensorDataInfoDialogController(QObject *parent) : QObject(parent),
	m_view(nullptr)
{

}

void SensorDataInfoDialogController::setView(SensorDataInfoDialog * const view)
{
    m_view = view;
}

SensorDataInfoDialog * const SensorDataInfoDialogController::view() const
{
    return m_view;
}

void SensorDataInfoDialogController::setSensors(const QVector<QJsonObject>&sensors)
{
	if (m_view)
	{
		m_view->setSensors(sensors);
	}
}
