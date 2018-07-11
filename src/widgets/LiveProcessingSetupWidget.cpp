#include "src/widgets/LiveProcessingSetupWidget.h"
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
