/***************************************************************************
File		: PreviewWidget.cpp
Project		: AdvBoard
Description	: Preview widget for the processing
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "src/widgets/PreviewWidget.h"
#include "ui_previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWidget)
{
    ui->setupUi(this);
}

PreviewWidget::~PreviewWidget()
{
    delete ui;
}

AdvVideoScene* PreviewWidget::advVideoScene() const
{
	return m_scene;
}

void PreviewWidget::setScene(AdvVideoScene * const scene)
{
	m_scene = scene;
	ui->previewGraphicsView->setScene(scene);
	ui->previewGraphicsView->update();
	ui->previewGraphicsView->viewport()->update();

	ui->previewGraphicsView->show();
}
