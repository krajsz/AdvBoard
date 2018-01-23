#include "SensorDataValidatingDialog.h"
#include "ui_sensordatavalidatingdialog.h"

SensorDataValidatingDialog::SensorDataValidatingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorDataValidatingDialog)
{
    ui->setupUi(this);
}

SensorDataValidatingDialog::~SensorDataValidatingDialog()
{
    delete ui;
}
