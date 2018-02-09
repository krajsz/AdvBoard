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

void LiveProcessingSetupWidget::setController(LiveProcessingSetupController *controller)
{
    m_controller = controller;
}

void LiveProcessingSetupWidget::sourceTypeChanged(int index)
{
    const LiveSensorDataReader::SourceType type = static_cast<LiveSensorDataReader::SourceType>(index);

    switch (type) {
    case LiveSensorDataReader::SourceType::File:
        ui->tcpHostLabel->setVisible(false);
        ui->tcpHostLineEdit->setVisible(false);

        ui->tcpPortLabel->setVisible(false);
        ui->tcpPortLineEdit->setVisible(false);

        ui->testTCPConnectionPushButton->setVisible(false);

        ui->fileNameLabel->setVisible(true);
        ui->fileNameLineEdit->setVisible(true);
        ui->openLiveFilePushButton->setVisible(true);
        break;
    case LiveSensorDataReader::SourceType::TCP:
        ui->tcpHostLabel->setVisible(true);
        ui->tcpHostLineEdit->setVisible(true);

        ui->tcpPortLabel->setVisible(true);
        ui->tcpPortLineEdit->setVisible(true);

        ui->testTCPConnectionPushButton->setVisible(true);

        ui->fileNameLabel->setVisible(false);
        ui->fileNameLineEdit->setVisible(false);
        ui->openLiveFilePushButton->setVisible(false);

        break;

    default:
        break;
    }
}
void LiveProcessingSetupWidget::previewEnabledChanged(bool enabled)
{
    if (enabled)
    {
        ui->fullscreenPreviewRadioButton->setEnabled(true);
        ui->normalPreviewRadioButton->setEnabled(true);
    }
    else
    {
        ui->fullscreenPreviewRadioButton->setEnabled(false);
        ui->normalPreviewRadioButton->setEnabled(false);
    }
}
void LiveProcessingSetupWidget::previewNormalChanged(bool checked)
{
    if (checked)
    {
        m_controller->setPreview(LiveProcessingSetupController::Preview::Normal);
    }
    else
    {
        m_controller->setPreview(LiveProcessingSetupController::Preview::Fullscreen);
    }
}
void LiveProcessingSetupWidget::intervalChanged(const int value)
{

}

void LiveProcessingSetupWidget::fileNameChanged(const QString& fileName)
{

}
void LiveProcessingSetupWidget::hostChanged(const QString& host)
{

}
void LiveProcessingSetupWidget::portChanged(const QString& port)
{

}

void LiveProcessingSetupWidget::openLiveFile()
{

}
