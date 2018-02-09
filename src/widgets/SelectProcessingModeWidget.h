/***************************************************************************
File		: SelectProcessingModeWidget.h
Project		: AdvBoard
Description	: Widget for selecting the processing type
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef SELECTPROCESSINGMODEWIDGET_H
#define SELECTPROCESSINGMODEWIDGET_H

#include <QWidget>

class QKeyEvent;
namespace Ui {
class SelectProcessingModeWidget;
}

class SelectProcessingModeWidget : public QWidget
{
    Q_OBJECT

public:
    enum ProcessingMode
    {
        PostProcessing = 0,
        LiveProcessing
    };
    explicit SelectProcessingModeWidget(QWidget *parent = 0);
    ~SelectProcessingModeWidget();

    ProcessingMode processingMode() const;
    void keyPressEvent(QKeyEvent *event);

protected:
private:
    Ui::SelectProcessingModeWidget *ui;
};

#endif // SELECTPROCESSINGMODEWIDGET_H
