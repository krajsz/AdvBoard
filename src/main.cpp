#include "src/AdvBoardMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdvBoardMain* advBoard;

    AdvMainController* controller = new AdvMainController;

    //if..

    advBoard = new AdvBoardMain;
    advBoard->setController(controller);
    advBoard->show();

    return a.exec();
}
