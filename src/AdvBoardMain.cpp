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
    ui(new Ui::AdvBoardMain),
    m_selectProcessingModeWidget(new SelectProcessingModeWidget),
    m_dashboardSetupWidget(nullptr),
    m_liveProcessingWidget(nullptr),
    m_postProcessingWidget(nullptr),
    m_previewWidget(nullptr)
{
    ui->setupUi(this);
    m_stackedWidget = ui->advBoardWidgets;

    m_stackedWidget->addWidget(m_selectProcessingModeWidget);
    m_stackedWidget->setCurrentWidget(m_selectProcessingModeWidget);

  /*  connect(ui->openSensorDataAction, &QAction::triggered, this, &AdvBoardMain::openSensorData);
    connect(ui->exitAppAction, &QAction::triggered, this, &AdvBoardMain::closeApp);
    connect(ui->aboutAction, &QAction::triggered, this, &AdvBoardMain::about);
    connect(ui->loadSensorDataButton, &QPushButton::clicked, this, &AdvBoardMain::openSensorData);
    connect(ui->loadVideoSourceButton, &QPushButton::clicked, this, &AdvBoardMain::openVideoSource);
    connect(ui->openVideoAction, &QAction::triggered, this, &AdvBoardMain::openVideoSource);
    connect(ui->showDataInfoDialog, &QPushButton::clicked, this, &AdvBoardMain::sensorDataInfoDialogButtonClicked);
    connect(ui->optionsAction, &QAction::triggered, this, &AdvBoardMain::optionsActionTriggered);
*/
    ui->backButton->setEnabled(false);

    ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->backButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));

    connect(ui->nextButton, &QPushButton::clicked, this, &AdvBoardMain::nextWidget);
    connect(ui->backButton, &QPushButton::clicked, this, &AdvBoardMain::previousWidget);
}

AdvBoardMain::~AdvBoardMain()
{
    delete m_controller;

    delete m_selectProcessingModeWidget;
    if (m_dashboardSetupWidget)
        delete m_dashboardSetupWidget;
    if (m_postProcessingWidget)
        delete m_postProcessingWidget;
    if (m_liveProcessingWidget)
        delete m_liveProcessingWidget;
    if (m_previewWidget)
        delete m_previewWidget;
    delete ui;
}

void AdvBoardMain::setController(AdvMainController *controller)
{
    m_controller = controller;
    /*m_view = ui->videoView;
    m_view->show();

    m_view->setController(m_controller->viewController());

    connect(m_controller, &AdvMainController::dashboardValid, this, &AdvBoardMain::dashboardValidation);
    connect(m_controller, &AdvMainController::sensorDataInvalid, this, &AdvBoardMain::sensorDataInvalid);
    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->viewController(), &AdvViewController::play);
    connect(ui->startProcessingButton, &QPushButton::clicked, m_controller->sensorDataReader(), &SensorDataReader::startReading);
*/
}

void AdvBoardMain::nextWidget()
{
    if (m_stackedWidget->currentWidget() == m_selectProcessingModeWidget)
    {
        SelectProcessingModeWidget::ProcessingMode processingMode = m_selectProcessingModeWidget->processingMode();
        if (processingMode == SelectProcessingModeWidget::ProcessingMode::LiveProcessing)
        {
            if (m_liveProcessingWidget == nullptr)
            {
                m_liveProcessingWidget = new LiveProcessingSetupWidget;

                m_stackedWidget->addWidget(m_liveProcessingWidget);
            }
            m_stackedWidget->setCurrentWidget(m_liveProcessingWidget);
        }
        else if (processingMode == SelectProcessingModeWidget::ProcessingMode::PostProcessing)
        {
            if (m_postProcessingWidget == nullptr)
            {
                m_postProcessingWidget = new PostProcessingSetupWidget;
                m_postProcessingWidget->setController(m_controller->postProcessingSetupController());
                m_stackedWidget->addWidget(m_postProcessingWidget);
            }
            m_stackedWidget->setCurrentWidget(m_postProcessingWidget);
        }

        ui->backButton->setEnabled(true);
    }
    else if ((m_stackedWidget->currentWidget() == m_liveProcessingWidget) ||
               (m_stackedWidget->currentWidget() == m_postProcessingWidget))
    {
        if (m_dashboardSetupWidget == nullptr)
        {
            m_dashboardSetupWidget = new DashboardSetupWidget;
            m_stackedWidget->addWidget(m_dashboardSetupWidget);
        }
        ui->nextButton->setText(tr("Start processing"));
        ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

        m_stackedWidget->setCurrentWidget(m_dashboardSetupWidget);
    }
    else if (m_stackedWidget->currentWidget() == m_dashboardSetupWidget)
    {
        //preview enabled?
        if (m_previewWidget == nullptr)
        {
            m_previewWidget = new PreviewWidget;
            m_stackedWidget->addWidget(m_previewWidget);
        }
        ui->nextButton->setText(tr("Stop processing"));
        ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

        m_stackedWidget->setCurrentWidget(m_previewWidget);
    }
}

void AdvBoardMain::previousWidget()
{
    if ((m_stackedWidget->currentWidget() == m_liveProcessingWidget) ||
            (m_stackedWidget->currentWidget() == m_postProcessingWidget))
    {
        ui->backButton->setEnabled(false);
        m_stackedWidget->setCurrentWidget(m_selectProcessingModeWidget);
    }
    else if (m_stackedWidget->currentWidget() == m_previewWidget)
    {
        // quit rendering?
        m_stackedWidget->setCurrentWidget(m_dashboardSetupWidget);
        ui->nextButton->setText(tr("Start processing"));
        ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else if (m_stackedWidget->currentWidget() == m_dashboardSetupWidget)
    {
        // lose changes?
        SelectProcessingModeWidget::ProcessingMode processingMode = m_selectProcessingModeWidget->processingMode();
        if (processingMode == SelectProcessingModeWidget::ProcessingMode::LiveProcessing)
        {
            m_stackedWidget->setCurrentWidget(m_liveProcessingWidget);
        }
        else if (processingMode == SelectProcessingModeWidget::ProcessingMode::PostProcessing)
        {
            m_stackedWidget->setCurrentWidget(m_postProcessingWidget);
        }
        ui->nextButton->setText(tr("Next"));
        ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
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
