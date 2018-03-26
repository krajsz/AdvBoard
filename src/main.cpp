#include "src/AdvBoardMain.h"
#include "src/controllers/AdvMainController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdvBoardMain* advBoard;

    AdvMainController* controller = new AdvMainController;

    //if..

    advBoard = new AdvBoardMain;
    controller->setView(advBoard);
    advBoard->show();

    return a.exec();
}
