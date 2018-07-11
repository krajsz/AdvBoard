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
#include <QProcessEnvironment>
#include <QTemporaryFile>
#include <QDebug>

ScriptsHandler* ScriptsHandler::scriptsHandler;

ScriptsHandler::ScriptsHandler(QObject *parent) : QObject(parent),
  m_script(new QProcess(this)),
  m_tempScriptFile(nullptr)
{
}

ScriptsHandler::~ScriptsHandler()
{
	delete m_tempScriptFile;
	delete m_script;
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
	QFile resFile(SENSOR_BOARD_HANDLER_SCRIPT_PATH);
	m_tempScriptFile = new QTemporaryFile;
	if (resFile.open(QFile::ReadOnly))
	{
		m_tempScriptFile = QTemporaryFile::createNativeFile(resFile);
		if (m_tempScriptFile->open())
		{
			QStringList args = QStringList() << m_tempScriptFile->fileName();

			for (const auto* const sensor: sensors)
			{
				const QString arg = QString::number(sensor->id()) + "_" + QString::number(sensor->type());
				args << arg;
			}
			for (const QString& arg : args)
				qDebug() << arg;
			QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

			m_script->setProcessEnvironment(env);
			m_script->setReadChannel(QProcess::ProcessChannel::StandardOutput);
			m_script->start("python", args);

			connect(m_script, &QProcess::started, this, &ScriptsHandler::scriptStarted);
			connect(m_script, &QProcess::stateChanged, this, &ScriptsHandler::stateChanged);

			connect(m_script, &QProcess::errorOccurred, this, &ScriptsHandler::scriptStartingError);
			connect(m_script, &QProcess::readyReadStandardOutput, this, &ScriptsHandler::handleInput);

			qDebug() << "Script started";
		}
	}
}

void ScriptsHandler::scriptStartingError(QProcess::ProcessError error)
{
	qDebug() << "Process error: " << m_script->errorString();
}

void ScriptsHandler::stateChanged(QProcess::ProcessState state)
{
	if (state == QProcess::ProcessState::NotRunning)
		emit scriptStopped();

	qDebug() << "State: " << state;
}

void ScriptsHandler::sendDataValid(bool valid)
{
	if (valid)
	{
		m_script->write(QByteArray("data:OK"));
	}
	else
	{
		m_script->write(QByteArray("data:NOK"));
	}
}

void ScriptsHandler::handleInput()
{
	const QString data = m_script->readAll();

	qDebug() << "Data from script: " << data;
}
