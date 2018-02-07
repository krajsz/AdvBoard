#ifndef VIDEOLOADINGDIALOG_H
#define VIDEOLOADINGDIALOG_H

#include <QDialog>
#include <QProgressBar>

namespace Ui {
class VideoLoadingDialog;
}

class VideoLoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoLoadingDialog(QWidget *parent = 0);
    ~VideoLoadingDialog();
private:
    Ui::VideoLoadingDialog *ui;
public slots:
    void setPercent(int value);
};

#endif // VIDEOLOADINGDIALOG_H
