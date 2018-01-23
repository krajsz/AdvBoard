#ifndef SENSORDATAVALIDATINGDIALOG_H
#define SENSORDATAVALIDATINGDIALOG_H

#include <QDialog>

namespace Ui {
class SensorDataValidatingDialog;
}

class SensorDataValidatingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorDataValidatingDialog(QWidget *parent = 0);
    ~SensorDataValidatingDialog();

private:
    Ui::SensorDataValidatingDialog *ui;
};

#endif // SENSORDATAVALIDATINGDIALOG_H
