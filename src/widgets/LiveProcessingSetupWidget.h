/***************************************************************************
File		: LiveProcessingSetupWidget.h
Project		: AdvBoard
Description	: Live processing setup widget
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
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

private slots:
    void sourceTypeChanged(int index);
    void previewEnabledChanged(bool enabled);
    void previewNormalChanged(bool checked);
    void intervalChanged(const int value);

    void fileNameChanged(const QString& fileName);
    void hostChanged(const QString& host);
    void portChanged(const QString& port);

    void openLiveFile();

signals:
    void setPreview(bool checked);
private:
    Ui::LiveProcessingSetupWidget *ui;
};

#endif // LIVEPROCESSINGSETUPWIDGET_H
