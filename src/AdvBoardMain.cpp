#include "AdvBoardMain.h"
#include "ui_advboardmain.h"

AdvBoardMain::AdvBoardMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdvBoardMain)
{
    ui->setupUi(this);
}

AdvBoardMain::~AdvBoardMain()
{
    delete ui;
}
