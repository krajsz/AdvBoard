#ifndef POSTPROCESSINGSETUPWIDGET_H
#define POSTPROCESSINGSETUPWIDGET_H

#include <QWidget>

namespace Ui {
class PostProcessingSetupWidget;
}

class PostProcessingSetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostProcessingSetupWidget(QWidget *parent = 0);
    ~PostProcessingSetupWidget();

private:
    Ui::PostProcessingSetupWidget *ui;
};

#endif // POSTPROCESSINGSETUPWIDGET_H
