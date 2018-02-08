#include "src\widgets\SensorDataValidationErrorsDialog.h"
#include "ui_sensordatavalidationerrorsdialog.h"

SensorDataValidationErrorsDialog::SensorDataValidationErrorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorDataValidationErrorsDialog)
{
    ui->setupUi(this);
}

SensorDataValidationErrorsDialog::~SensorDataValidationErrorsDialog()
{
    delete ui;
}
