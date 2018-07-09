/***************************************************************************
File		: ScriptsHandler.h
Project		: AdvBoard
Description	: Python script handler
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/

#ifndef SCRIPTSHANDLER_H
#define SCRIPTSHANDLER_H

#include <QObject>
#include <QVector>
#include <QProcess>

class AbstractSensor;
class QString;
class QTemporaryFile;
class ScriptsHandler : public QObject
{
	Q_OBJECT
public:
	static ScriptsHandler* instance();
	void startScript(const QVector<AbstractSensor*>& sensors);
	~ScriptsHandler();
	void sendDataValid(bool valid);
signals:
	void startDataReadingButtonPressed();
	void checkSensorBoardDataButtonPressed();
	void scriptStopped();
public slots:

private slots:
	void handleInput();
	void scriptStarted();
	void stateChanged(QProcess::ProcessState state);
	void scriptStartingError(QProcess::ProcessError error);
private:
	QTemporaryFile* m_tempScriptFile;
	static ScriptsHandler* scriptsHandler;
	const QString SENSOR_BOARD_HANDLER_SCRIPT_PATH = ":/scripts/scripts/sensorBoardHandler.py";

	explicit ScriptsHandler(QObject *parent = nullptr);

	QProcess* m_script;
};

#endif // SCRIPTSHANDLER_H
