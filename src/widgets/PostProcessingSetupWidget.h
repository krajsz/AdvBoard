/***************************************************************************
File		: PostProcessingSetupWidget.cpp
Project		: AdvBoard
Description	: Postprocessing setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef POSTPROCESSINGSETUPWIDGET_H
#define POSTPROCESSINGSETUPWIDGET_H
#include "src/widgets/SensorDataInfoDialog.h"

#include <QWidget>

namespace Ui {
class PostProcessingSetupWidget;
}

class PostProcessingSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostProcessingSetupWidget(QWidget *parent = 0);
    ~PostProcessingSetupWidget();

private:
    Ui::PostProcessingSetupWidget *ui;
    SensorDataInfoDialog* m_sensorDataInfoDialog;
private slots:
    void openVideoSource();
    void sensorDataInfoDialogButtonClicked();
};

#endif // POSTPROCESSINGSETUPWIDGET_H
