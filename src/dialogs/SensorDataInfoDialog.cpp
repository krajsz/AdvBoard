#include "SensorDataInfoDialog.h"
#include "ui_SensorDataInfoDialog.h"

SensorDataInfoDialog::SensorDataInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorDataInfoDialog)
{
    ui->setupUi(this);
}

SensorDataInfoDialog::~SensorDataInfoDialog()
{
    delete ui;
}
