#ifndef VIDEOINFODIALOG_H
#define VIDEOINFODIALOG_H

#include <QDialog>
#include "src/controllers/VideoInfoDialogController.h"

namespace Ui {
class VideoInfoDialog;
}

class VideoInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoInfoDialog(QWidget *parent = 0);
    ~VideoInfoDialog();
    void setController(VideoInfoDialogController* controller);
private:
    Ui::VideoInfoDialog *ui;
    VideoInfoDialogController* m_controller;
};

#endif // VIDEOINFODIALOG_H
