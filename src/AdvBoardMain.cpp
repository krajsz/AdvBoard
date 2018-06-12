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
#include <QKeyEvent>
#include <QStyle>

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
	connect(ui->optionsAction, &QAction::triggered, this, &AdvBoardMain::optionsActionTriggered);
*/
	connect(ui->nextButton, &QPushButton::clicked, this, &AdvBoardMain::emitStartProcessing);
	ui->backButton->setEnabled(false);

	ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
	ui->backButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));

	connect(ui->nextButton, &QPushButton::clicked, this, &AdvBoardMain::nextWidget);
	connect(ui->backButton, &QPushButton::clicked, this, &AdvBoardMain::previousWidget);
}

LiveProcessingSetupWidget* AdvBoardMain::liveProcessingSetupWidget()
{
	if (m_liveProcessingWidget == nullptr)
	{
		m_liveProcessingWidget = new LiveProcessingSetupWidget;
		m_stackedWidget->addWidget(m_liveProcessingWidget);
	}

	return m_liveProcessingWidget;
}

PostProcessingSetupWidget* AdvBoardMain::postProcessingSetupWidget()
{
	if (m_postProcessingWidget == nullptr)
	{
		m_postProcessingWidget = new PostProcessingSetupWidget;
		connect(m_postProcessingWidget, &PostProcessingSetupWidget::ready, this, &AdvBoardMain::dataReady);
		m_stackedWidget->addWidget(m_postProcessingWidget);
	}

	return m_postProcessingWidget;
}

DashboardSetupWidget* AdvBoardMain::dashBoardSetupWidget()
{
	if (m_dashboardSetupWidget == nullptr)
	{
		m_dashboardSetupWidget = new DashboardSetupWidget;
		m_stackedWidget->addWidget(m_dashboardSetupWidget);
	}

	return m_dashboardSetupWidget;
}

PreviewWidget* AdvBoardMain::previewWidget()
{
	if (m_previewWidget == nullptr)
	{
		m_previewWidget = new PreviewWidget;
		m_stackedWidget->addWidget(m_previewWidget);
	}

	return m_previewWidget;
}

AdvBoardMain::~AdvBoardMain()
{
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

void AdvBoardMain::keyPressEvent(QKeyEvent *event)
{
	if (m_stackedWidget->currentWidget() == m_selectProcessingModeWidget)
	{
		m_selectProcessingModeWidget->keyPressEvent(event);
	}

	if (event->key() == Qt::Key_N)
	{
		emit ui->nextButton->clicked();
	}
	else if (event->key() == Qt::Key_B)
	{
		if (ui->backButton->isEnabled())
		{
			emit ui->backButton->clicked();
		}
	}
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
			emit nextButtonLiveProcessing();

			m_stackedWidget->setCurrentWidget(m_liveProcessingWidget);
		}
		else if (processingMode == SelectProcessingModeWidget::ProcessingMode::PostProcessing)
		{
			if (m_postProcessingWidget == nullptr)
			{
				m_postProcessingWidget = new PostProcessingSetupWidget;
				connect(m_postProcessingWidget, &PostProcessingSetupWidget::ready, this, &AdvBoardMain::dataReady);
				m_stackedWidget->addWidget(m_postProcessingWidget);
			}

			emit nextButtonPostProcessing();

			m_stackedWidget->setCurrentWidget(m_postProcessingWidget);
		}

		ui->nextButton->setEnabled(false);
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

		if (m_stackedWidget->currentWidget() == m_liveProcessingWidget)
		{
			emit nextButtonDashboardSetup(SelectProcessingModeWidget::ProcessingMode::LiveProcessing);
		}

		if (m_stackedWidget->currentWidget() == m_postProcessingWidget)
		{
			emit nextButtonDashboardSetup(SelectProcessingModeWidget::ProcessingMode::PostProcessing);
		}

		ui->nextButton->setText(tr("Start processing"));
		ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

		m_stackedWidget->setCurrentWidget(m_dashboardSetupWidget);
	}
	else if (m_stackedWidget->currentWidget() == m_dashboardSetupWidget)
	{
		//preview enabled?
		previewWidget();

		ui->nextButton->setText(tr("Stop processing"));
		ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

		m_stackedWidget->setCurrentWidget(m_previewWidget);

		emit nextButtonPreviewWidget();
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

void AdvBoardMain::dataReady(bool ready)
{
	if (ready)
	{
		ui->nextButton->setEnabled(true);
	}
}

void AdvBoardMain::emitStartProcessing()
{
	if (m_stackedWidget->currentWidget() == m_dashboardSetupWidget)
	{
		emit startProcessing();
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
