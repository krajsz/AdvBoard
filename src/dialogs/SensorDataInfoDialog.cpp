#include "SensorDataInfoDialog.h"
#include "ui_SensorDataInfoDialog.h"

SensorDataInfoDialog::SensorDataInfoDialog(const SensorDataReader& data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorDataInfoDialog)
{
    ui->setupUi(this);
}

void SensorDataInfoDialog::setController(SensorDataInfoDialogController *controller)
{
    m_controller = controller;
}

SensorDataInfoDialog::~SensorDataInfoDialog()
{
    delete ui;
}
