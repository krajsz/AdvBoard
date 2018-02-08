#ifndef SENSORDATAVALIDATIONERRORSDIALOG_H
#define SENSORDATAVALIDATIONERRORSDIALOG_H

#include <QDialog>

namespace Ui {
class SensorDataValidationErrorsDialog;
}

class SensorDataValidationErrorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorDataValidationErrorsDialog(QWidget *parent = 0);
    ~SensorDataValidationErrorsDialog();

private:
    Ui::SensorDataValidationErrorsDialog *ui;
};

#endif // SENSORDATAVALIDATIONERRORSDIALOG_H
