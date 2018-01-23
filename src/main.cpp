#include "AdvBoardMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdvBoardMain w;
    w.show();

    return a.exec();
}
