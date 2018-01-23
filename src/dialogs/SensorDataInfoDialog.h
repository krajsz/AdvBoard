#ifndef SENSORDATAINFODIALOG_H
#define SENSORDATAINFODIALOG_H

#include <QDialog>
#include "SensorData.h"

namespace Ui {
class SensorDataInfoDialog;
}

class SensorDataInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorDataInfoDialog(QWidget *parent = 0, const SensorData& data);
    ~SensorDataInfoDialog();

private:
    Ui::SensorDataInfoDialog *ui;
};

#endif // SENSORDATAINFODIALOG_H
