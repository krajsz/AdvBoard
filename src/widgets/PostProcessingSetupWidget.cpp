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

void PostProcessingSetupWidget::setController(PostProcessingSetupController *controller)
{
    m_controller = controller;
    connect(m_controller, &PostProcessingSetupController::videoLoadedSignal, this, &PostProcessingSetupWidget::videoLoaded);
    connect(m_controller, &PostProcessingSetupController::sensorDataIsValid, this, &PostProcessingSetupWidget::sensorDataIsValid);
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

    m_sensorDataInfoDialog->setSensors(m_controller->sensorDataReader()->sensorData());
    m_sensorDataInfoDialog->show();
}

void PostProcessingSetupWidget::videoLoaded()
{
    emit ready(m_controller->ready());
}

void PostProcessingSetupWidget::sensorDataIsValid(bool valid)
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

    emit ready(m_controller->ready());
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
    m_controller->setResolutionWidth(value);
    ui->predefinedResolutionsComboBox->setCurrentIndex(0);
}
void PostProcessingSetupWidget::resolutionHeightChanged(int value)
{
    m_controller->setResolutionHeight(value);
    ui->predefinedResolutionsComboBox->setCurrentIndex(0);
}
void PostProcessingSetupWidget::resolutionPredefinedChanged(int index)
{
    const PostProcessingSetupController::PredefinedSizes size = static_cast<PostProcessingSetupController::PredefinedSizes>(index);
    switch (size) {
    case PostProcessingSetupController::PredefinedSizes::FHD:
        ui->xResolutionSpinBox->setValue(1920);
        ui->yResolutionSpinBox->setValue(1080);
        break;
    case PostProcessingSetupController::PredefinedSizes::HD:
        ui->xResolutionSpinBox->setValue(1280);
        ui->yResolutionSpinBox->setValue(720);
        break;
    case PostProcessingSetupController::PredefinedSizes::VGA:
        ui->xResolutionSpinBox->setValue(640);
        ui->yResolutionSpinBox->setValue(480);
        break;
    default:
        break;
    }
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
    m_controller->loadSensorData(":/json/data/testnew.json");
}
void PostProcessingSetupWidget::loadVideoSource()
{
    const QUrl path = QUrl::fromLocalFile(QFileDialog::getOpenFileName(0, tr("Open your video"), QDir::homePath()));

    m_controller->loadVideoSource(path);
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
