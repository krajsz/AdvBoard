#include "src/widgets/ValidationErrorsDialog.h"
#include "ui_validationerrorsdialog.h"

ValidationErrorsDialog::ValidationErrorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValidationErrorsDialog)
{
    ui->setupUi(this);
}

ValidationErrorsDialog::~ValidationErrorsDialog()
{
    delete ui;
}
