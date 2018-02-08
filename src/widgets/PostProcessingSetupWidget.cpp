/***************************************************************************
File		: PostProcessingSetupWidget.cpp
Project		: AdvBoard
Description	: Postprocessing setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src\widgets\PostProcessingSetupWidget.h"
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
    connect(ui->loadVideoSourceButton, &QPushButton::clicked, this, &PostProcessingSetupWidget::openVideoSource);
}

PostProcessingSetupWidget::~PostProcessingSetupWidget()
{
    delete ui;
}

void PostProcessingSetupWidget::sensorDataInfoDialogButtonClicked()
{
    if (m_sensorDataInfoDialog == nullptr)
    {
        m_sensorDataInfoDialog = new SensorDataInfoDialog();
    }

    QVector<AbstractSensor*> sensors;
    /*for (AdvSensorItem* sensorItem : m_view->videoScene()->dashboard()->sensorItems())
    {
        AbstractSensor* sensor = sensorItem->sensor();
        sensors.push_back(sensor);
    }*/
    m_sensorDataInfoDialog->show();
    m_sensorDataInfoDialog->setSensors(sensors);
}

void PostProcessingSetupWidget::openVideoSource()
{
    /*const QUrl path = QFileDialog::getOpenFileName(0, tr("Open your video"), QDir::homePath());

    VideoLoadingDialog* dialog = new VideoLoadingDialog;
    connect(m_view->videoScene()->video(), &VideoSource::loadPercent, dialog, &VideoLoadingDialog::setPercent);
    connect(m_view->videoScene()->video(), &VideoSource::videoLoaded, dialog, &VideoLoadingDialog::close);
    connect(m_view->videoScene()->video(), &VideoSource::videoLoaded, this, [=](){
        ui->startProcessingButton->setEnabled(true);
    });

    emit m_controller->viewController()->setVideo(path);
    dialog->show();*/
}

/*
void AdvBoardMain::dashboardValidation(bool valid)
{
    if (valid)
    {
        ui->validLabel->setText("Dashboard Valid");
    }
    else
    {
        ui->validLabel->setText("Dashboard Invalid");
    }
}*/
