/***************************************************************************
File		: SelectProcessingModeWidget.cpp
Project		: AdvBoard
Description	: Widget for selecting the processing type
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/widgets/SelectProcessingModeWidget.h"
#include "ui_selectprocessingmodewidget.h"


#include <QKeyEvent>

SelectProcessingModeWidget::SelectProcessingModeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectProcessingModeWidget)
{
    ui->setupUi(this);
}

SelectProcessingModeWidget::~SelectProcessingModeWidget()
{
    delete ui;
}

SelectProcessingModeWidget::ProcessingMode SelectProcessingModeWidget::processingMode() const
{
    if (ui->liveProcessingRadioButton->isChecked())
    {
        return SelectProcessingModeWidget::ProcessingMode::LiveProcessing;
    }
    return SelectProcessingModeWidget::ProcessingMode::PostProcessing;
}

void SelectProcessingModeWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_P)
    {
        ui->postProcessingRadioButton->setChecked(true);
    }
    else if (event->key() == Qt::Key_L)
    {
        ui->liveProcessingRadioButton->setChecked(true);
    }
}
