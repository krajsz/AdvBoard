#include "src\widgets\PostProcessingSetupWidget.h"
#include "ui_postprocessingsetupwidget.h"

PostProcessingSetupWidget::PostProcessingSetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PostProcessingSetupWidget)
{
    ui->setupUi(this);
}

PostProcessingSetupWidget::~PostProcessingSetupWidget()
{
    delete ui;
}
