#include "VideoInfoDialog.h"
#include "ui_videoinfodialog.h"

VideoInfoDialog::VideoInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoInfoDialog)
{
    ui->setupUi(this);
}

VideoInfoDialog::~VideoInfoDialog()
{
    delete ui;
}
