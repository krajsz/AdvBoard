#ifndef LIVEPROCESSINGSETUPWIDGET_H
#define LIVEPROCESSINGSETUPWIDGET_H

#include <QWidget>

namespace Ui {
class LiveProcessingSetupWidget;
}

class LiveProcessingSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LiveProcessingSetupWidget(QWidget *parent = 0);
    ~LiveProcessingSetupWidget();

private:
    Ui::LiveProcessingSetupWidget *ui;
};

#endif // LIVEPROCESSINGSETUPWIDGET_H