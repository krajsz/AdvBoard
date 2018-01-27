#include "src/dialogs/VideoLoadingDialog.h"
#include "ui_videoloadingdialog.h"

#include <QDebug>

VideoLoadingDialog::VideoLoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoLoadingDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

VideoLoadingDialog::~VideoLoadingDialog()
{
    delete ui;
}

void VideoLoadingDialog::setPercent(int value)
{
    qDebug() << "percent: " << value;
    ui->videoLoadedProgressBar->setValue(value);
}
