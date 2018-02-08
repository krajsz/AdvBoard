/***************************************************************************
File		: LiveProcessingSetupWidget.cpp
Project		: AdvBoard
Description	: Live processing setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src\widgets\LiveProcessingSetupWidget.h"
#include "ui_liveprocessingsetupwidget.h"

LiveProcessingSetupWidget::LiveProcessingSetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveProcessingSetupWidget)
{
    ui->setupUi(this);
}

LiveProcessingSetupWidget::~LiveProcessingSetupWidget()
{
    delete ui;
}
