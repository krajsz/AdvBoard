/***************************************************************************
File		: PostProcessingSetupWidget.cpp
Project		: AdvBoard
Description	: Postprocessing setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/widgets/PostProcessingSetupWidget.h"
#include "src/widgets/VideoLoadingDialog.h"
#include "src/view/AdvSensorItem.h"
#include "ui_postprocessingsetupwidget.h"

#include <QUrl>
#include <QFileDialog>
#include <QDir>
#include <QVector>

PostProcessingSetupWidget::PostProcessingSetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PostProcessingSetupWidget)
{
    ui->setupUi(this);

    connect(ui->showDataInfoDialog, &QPushButton::clicked, this, &PostProcessingSetupWidget::sensorDataInfoDialogButtonClicked);
    connect(ui->resizePercentSlider, &QSlider::valueChanged, ui->resizeSpinBox, &QSpinBox::setValue);
    connect(ui->resizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->resizePercentSlider, &QSlider::setValue);
    connect(ui->previewCheckBox, &QCheckBox::toggled, this, &PostProcessingSetupWidget::previewEnabledChecked);
    connect(ui->processingSettingsSameAsSourceCheckBox, &QCheckBox::toggled, this, &PostProcessingSetupWidget::sameAsSourceChecked);
    connect(ui->predefinedResolutionsComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PostProcessingSetupWidget::resolutionPredefinedChanged);
    connect(ui->xResolutionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PostProcessingSetupWidget::resolutionWidthChanged);
    connect(ui->yResolutionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PostProcessingSetupWidget::resolutionHeightChanged);
    connect(ui->loadSensorDataButton, &QPushButton::clicked, this, &PostProcessingSetupWidget::loadSensorData);
    connect(ui->loadVideoSourceButton, &QPushButton::clicked, this, &PostProcessingSetupWidget::loadVideoSource);

    ui->showValidationErrorsButton->hide();
}

void PostProcessingSetupWidget::setResolution(const QSize &resolution)
{
    ui->xResolutionSpinBox->setValue(resolution.width());
    ui->yResolutionSpinBox->setValue(resolution.height());
}

PostProcessingSetupWidget::~PostProcessingSetupWidget()
{
    delete ui;
}

void PostProcessingSetupWidget::previewEnabledChecked(bool checked)
{
    if (checked)
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

void PostProcessingSetupWidget::sensorDataInfoDialogButtonClicked()
{
    if (m_sensorDataInfoDialog == nullptr)
    {
        m_sensorDataInfoDialog = new SensorDataInfoDialog();
    }

    emit sensorDataInfoDialogButtonClickedSignal();
   // m_sensorDataInfoDialog->setSensors(m_controller->sensorDataReader()->sensorData());
    m_sensorDataInfoDialog->show();
}

void PostProcessingSetupWidget::videoLoaded(bool bready)
{
    emit ready(bready);
}

void PostProcessingSetupWidget::sensorDataIsValid(bool valid, bool bready)
{
    if (valid)
    {
        ui->sensorDataValidLabel->setText("Valid sensor data");
    }
    else
    {
        ui->showValidationErrorsButton->show();
        ui->sensorDataValidLabel->setText("Invalid sensor data");
    }

    emit ready(bready);
}

void PostProcessingSetupWidget::keepAspectRatioChecked(bool checked)
{
    if (checked)
    {

    }
    else
    {

    }
}

void PostProcessingSetupWidget::resizeChecked(bool checked)
{

}
void PostProcessingSetupWidget::sameAsSourceChecked(bool checked)
{
    if (checked)
    {
        ui->saveToFormat->setEnabled(false);
        ui->keepAspectRatioCheckBox->setEnabled(false);
        ui->predefinedResolutionsComboBox->setEnabled(false);
        ui->resizePercentSlider->setEnabled(false);
        ui->resizeSpinBox->setEnabled(false);
        ui->xResolutionSpinBox->setEnabled(false);
        ui->yResolutionSpinBox->setEnabled(false);
    }
    else
    {
        ui->saveToFormat->setEnabled(true);
        ui->keepAspectRatioCheckBox->setEnabled(true);
        ui->predefinedResolutionsComboBox->setEnabled(true);
        ui->resizePercentSlider->setEnabled(true);
        ui->resizeSpinBox->setEnabled(true);
        ui->xResolutionSpinBox->setEnabled(true);
        ui->yResolutionSpinBox->setEnabled(true);
    }
}

void PostProcessingSetupWidget::resizePercentageSliderValueChanged(int value)
{

}

void PostProcessingSetupWidget::resizePercentageSpinboxValueChanged(int value)
{

}

void PostProcessingSetupWidget::resolutionWidthChanged(int value)
{
    emit resolutionWidthChangedSignal(value);
    ui->predefinedResolutionsComboBox->setCurrentIndex(0);
}
void PostProcessingSetupWidget::resolutionHeightChanged(int value)
{
    emit resolutionHeightChangedSignal(value);
    ui->predefinedResolutionsComboBox->setCurrentIndex(0);
}
void PostProcessingSetupWidget::resolutionPredefinedChanged(int index)
{
    emit resolutionPredefinedChangedSignal(index);
}

void PostProcessingSetupWidget::videoFormatChanged(int index)
{

}
void PostProcessingSetupWidget::previewTypeChecked(bool checked)
{
    if (checked)
    {

    }
    else
    {

    }
}

void PostProcessingSetupWidget::loadSensorData()
{
    emit loadSensorDataSignal(QLatin1String(":/json/data/testnew.json"));
}
void PostProcessingSetupWidget::loadVideoSource()
{
    const QUrl path = QUrl::fromLocalFile(QFileDialog::getOpenFileName(0, tr("Open your video"), QDir::homePath()));

    emit loadVideoSourceSignal(path);
}

void PostProcessingSetupWidget::showVideoInfo()
{

}
void PostProcessingSetupWidget::showSensorInfo()
{

}

void PostProcessingSetupWidget::showSensorValidationErrors()
{

}
