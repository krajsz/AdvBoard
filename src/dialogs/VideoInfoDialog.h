#ifndef VIDEOINFODIALOG_H
#define VIDEOINFODIALOG_H

#include <QDialog>

namespace Ui {
class VideoInfoDialog;
}

class VideoInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoInfoDialog(QWidget *parent = 0);
    ~VideoInfoDialog();

private:
    Ui::VideoInfoDialog *ui;
};

#endif // VIDEOINFODIALOG_H
