/***************************************************************************
File		: SensorDataInfoDialogController.cpp
Project		: AdvBoard
Description	: Controller class of SensorDataInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "SensorDataInfoDialogController.h"

SensorDataInfoDialogController::SensorDataInfoDialogController(QObject *parent) : QObject(parent)
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
