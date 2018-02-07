#include "src/widgets/VideoInfoDialog.h"
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

void VideoInfoDialog::setController(VideoInfoDialogController *controller)
{
    m_controller = controller;
}
