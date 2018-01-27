#ifndef SENSORDATAVALIDATINGDIALOG_H
#define SENSORDATAVALIDATINGDIALOG_H

#include <QDialog>
#include "src/controllers/SensorDataValidatingDialogController.h"

namespace Ui {
class SensorDataValidatingDialog;
}

class SensorDataValidatingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorDataValidatingDialog(QWidget *parent = 0);
    ~SensorDataValidatingDialog();
    void setController(SensorDataValidatingDialogController* controller);
private:
    Ui::SensorDataValidatingDialog *ui;
    SensorDataValidatingDialogController* m_controller;
};

#endif // SENSORDATAVALIDATINGDIALOG_H
