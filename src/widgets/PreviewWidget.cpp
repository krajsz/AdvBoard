#include "src\widgets\PreviewWidget.h"
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
