/***************************************************************************
File		: SensorDataInfoDialogController.h
Project		: AdvBoard
Description	: Controller class for SensorDataInfoDialog
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SENSORDATAINFODIALOGCONTROLLER_H
#define SENSORDATAINFODIALOGCONTROLLER_H
#include "src/widgets/SensorDataInfoDialog.h"

#include <QObject>

class SensorDataInfoDialogController : public QObject
{
    Q_OBJECT
public:
    explicit SensorDataInfoDialogController(QObject *parent = nullptr);
    void setView(SensorDataInfoDialog* const view);
    SensorDataInfoDialog* const view() const;
	void setSensors(const QVector<QJsonObject> &sensors);
signals:

public slots:
private:
    SensorDataInfoDialog* m_view;
};

#endif // SENSORDATAINFODIALOGCONTROLLER_H
