/***************************************************************************
File		: PreviewWidget.cpp
Project		: AdvBoard
Description	: Preview widget for the processing
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class PreviewWidget;
}

class PreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget *parent = 0);
    ~PreviewWidget();

private:
    Ui::PreviewWidget *ui;
};

#endif // PREVIEWWIDGET_H
