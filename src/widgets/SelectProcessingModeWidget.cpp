#include "src\widgets\SelectProcessingModeWidget.h"
#include "ui_selectprocessingmodewidget.h"

SelectProcessingModeWidget::SelectProcessingModeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectProcessingModeWidget)
{
    ui->setupUi(this);
}

SelectProcessingModeWidget::~SelectProcessingModeWidget()
{
    delete ui;
}
