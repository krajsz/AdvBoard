/***************************************************************************
File		: ScriptsHandler.cpp
Project		: AdvBoard
Description	: Python script handler
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/

#include "src/ScriptsHandler.h"
#include "src/sensors/AbstractSensor.h"

#include <QProcess>

#include <QDebug>

ScriptsHandler* ScriptsHandler::scriptsHandler;

ScriptsHandler::ScriptsHandler(QObject *parent) : QObject(parent),
  m_script(new QProcess(this))
{
}

ScriptsHandler* ScriptsHandler::instance()
{
	if (scriptsHandler == nullptr)
	{
		scriptsHandler = new ScriptsHandler;
	}

	return scriptsHandler;
}

void ScriptsHandler::scriptStarted()
{
	qDebug() << "Started";
}

void ScriptsHandler::startScript(const QVector<AbstractSensor *> &sensors)
{
	QStringList args = QStringList() << SENSOR_BOARD_HANDLER_SCRIPT_PATH;
	qDebug() << "Script args: ";

	for (const auto* const sensor: sensors)
	{
		const QString arg = QString::number(sensor->id()) + "_" + QString::number(sensor->type());
		args << arg;

		qDebug() << arg;
	}
	m_script->setReadChannel(QProcess::ProcessChannel::StandardOutput);
	qDebug() << "StartDetached: " << m_script->startDetached("python", args);

	connect(m_script, &QProcess::started, this, &ScriptsHandler::scriptStarted);
	connect(m_script, &QProcess::stateChanged, this, &ScriptsHandler::stateChanged);

	connect(m_script, &QProcess::errorOccurred, this, &ScriptsHandler::scriptStartingError);
	connect(m_script, &QProcess::readyReadStandardOutput, this, &ScriptsHandler::handleInput);

	qDebug() << "Script started";
}

void ScriptsHandler::scriptStartingError(QProcess::ProcessError error)
{
	qDebug() << "Process error: " << m_script->errorString();
}

void ScriptsHandler::stateChanged(QProcess::ProcessState state)
{
	qDebug() << "State: " << state;
}

void ScriptsHandler::sendDataValid(bool valid)
{
	if (valid)
	{

	}
	else
	{

	}
}

void ScriptsHandler::handleInput()
{
	const QString data = m_script->readAll();

	qDebug() << "Data from script: " << data;
}
