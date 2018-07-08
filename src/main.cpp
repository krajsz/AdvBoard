#include "src/AdvBoardMain.h"
#include "src/controllers/AdvMainController.h"

#include "src/ScriptsHandler.h"

#include "src/sensors/Sensors.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdvBoardMain* advBoard;

    AdvMainController* controller = new AdvMainController;

	HumiditySensor* hum = new HumiditySensor(1);
	TemperatureSensor* temp = new TemperatureSensor(3);

	QVector<AbstractSensor*> sensors;
	sensors.push_back(hum);
	sensors.push_back(temp);

	ScriptsHandler* scriptHandler = ScriptsHandler::instance();
	scriptHandler->startScript(sensors);

	//if..
    advBoard = new AdvBoardMain;
    controller->setView(advBoard);
    advBoard->show();

    return a.exec();
}
