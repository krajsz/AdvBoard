/***************************************************************************
File		: SensorDataInfoDialog.h
Project		: AdvBoard
Description	: Class for SensorDataInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORDATAINFODIALOG_H
#define SENSORDATAINFODIALOG_H

#include <QDialog>
#include "src/datasources/SensorDataReader.h"
#include "src/controllers/SensorDataInfoDialogController.h"
#include "src/sensors/AbstractSensor.h"

namespace Ui {
class SensorDataInfoDialog;
}

class SensorDataInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorDataInfoDialog(QWidget *parent = 0);
    ~SensorDataInfoDialog();
    void setSensors(const QVector<QJsonObject> &sensors);

    void setController(SensorDataInfoDialogController* controller);

private:
    Ui::SensorDataInfoDialog *ui;
    SensorDataInfoDialogController* m_controller;
};

#endif // SENSORDATAINFODIALOG_H
