#ifndef SELECTPROCESSINGMODEWIDGET_H
#define SELECTPROCESSINGMODEWIDGET_H

#include <QWidget>

namespace Ui {
class SelectProcessingModeWidget;
}

class SelectProcessingModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectProcessingModeWidget(QWidget *parent = 0);
    ~SelectProcessingModeWidget();

private:
    Ui::SelectProcessingModeWidget *ui;
};

#endif // SELECTPROCESSINGMODEWIDGET_H
