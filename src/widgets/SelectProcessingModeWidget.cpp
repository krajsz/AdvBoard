/***************************************************************************
File		: SelectProcessingModeWidget.cpp
Project		: AdvBoard
Description	: Widget for selecting the processing type
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src\widgets\SelectProcessingModeWidget.h"
#include "ui_selectprocessingmodewidget.h"

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
