/***************************************************************************
File		: AdvBoardMain.cpp
Project		: AdvBoard
Description	: Main window
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "AdvBoardMain.h"
#include "ui_advboardmain.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QString>

AdvBoardMain::AdvBoardMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdvBoardMain)
{
    ui->setupUi(this);

    connect(ui->openSensorDataAction, &QAction::triggered, this, &AdvBoardMain::openSensorData);
    connect(ui->exitAppAction, &QAction::triggered, this, &AdvBoardMain::closeApp);
    connect(ui->aboutAction, &QAction::triggered, this, &AdvBoardMain::about);
    connect(ui->loadSensorDataButton, &QPushButton::clicked, this, &AdvBoardMain::openSensorData);
    connect(ui->loadVideoSourceButton, &QPushButton::clicked, this, &AdvBoardMain::openVideoSource);
    connect(ui->liveProcessingCheckBox, &QCheckBox::toggled, this, &AdvBoardMain::liveProcessingChecked);
    connect(ui->liveProcessingSettingsPushButton, &QPushButton::clicked, this, &AdvBoardMain::liveProcessingButtonClicked);
    connect(ui->openVideoAction, &QAction::triggered, this, &AdvBoardMain::openVideoSource);
    connect(ui->showDataInfoDialog, &QPushButton::clicked, this, &AdvBoardMain::sensorDataInfoDialogButtonClicked);
    connect(ui->showVideoInfoDialog, &QPushButton::clicked, this, &AdvBoardMain::videoInfoDialogButtonClicked);
    connect(ui->optionsAction, &QAction::triggered, this, &AdvBoardMain::optionsActionTriggered);

    ui->startProcessingButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->startProcessingButton->setEnabled(false);
}

AdvBoardMain::~AdvBoardMain()
{
    delete m_controller;
    delete m_view;

    delete ui;
}

void AdvBoardMain::setController(AdvMainController *controller)
{
    m_controller = controller;
    m_view = ui->videoView;
    m_view->show();
    m_view->setController(m_controller->viewController());

    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->viewController(), &AdvViewController::play);
    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->sensorDataReader(), &SensorDataReader::startReading);
}

void AdvBoardMain::openSensorData()
{
    //QString fileName = QFileDialog::getOpenFileName(0, tr("Open sensor data"), QDir::homePath(), "JSON (*.JSON *.json);");

    m_controller->sensorDataReader()->setFile(":/json/data/test.json");
    connect(m_controller->sensorDataReader(), &SensorDataReader::dataInvalid, this, &AdvBoardMain::sensorDataInvalid);
}

void AdvBoardMain::openVideoSource()
{
    QUrl path = QFileDialog::getOpenFileName(0, tr("Open your video"), QDir::home().absolutePath());

    VideoLoadingDialog* dialog = new VideoLoadingDialog;
    connect(m_view->videoScene()->video(), &VideoSource::loadPercent, dialog, &VideoLoadingDialog::setPercent);
    connect(m_view->videoScene()->video(), &VideoSource::videoLoaded, dialog, &VideoLoadingDialog::close);
    connect(m_view->videoScene()->video(), &VideoSource::videoLoaded, this, [=](){
        ui->startProcessingButton->setEnabled(true);
    });

    emit m_controller->viewController()->setVideo(path);
    dialog->show();
}

void AdvBoardMain::sensorDataInfoDialogButtonClicked()
{

}

void AdvBoardMain::videoInfoDialogButtonClicked()
{

}

void AdvBoardMain::startProcessing()
{

}

void AdvBoardMain::liveProcessingButtonClicked()
{

}

void AdvBoardMain::liveProcessingChecked(bool checked)
{
    if (checked)
    {
        ui->liveProcessingSettingsPushButton->setEnabled(true);
        ui->loadSourcesGroupBox->setEnabled(false);
    }
    else
    {
        ui->liveProcessingSettingsPushButton->setEnabled(false);
        ui->loadSourcesGroupBox->setEnabled(false);
    }
}

void AdvBoardMain::closeApp()
{
    close();
}

void AdvBoardMain::about()
{
    QMessageBox::information(0, tr("About"), "Author: Fábián Kristóf - Szabolcs", QMessageBox::Ok);
}

void AdvBoardMain::sensorDataInvalid(const QString &errorstring)
{
    QMessageBox::warning(0, tr("Sensor Data Invalid"), errorstring, QMessageBox::Ok);
}
void AdvBoardMain::optionsActionTriggered()
{

}
