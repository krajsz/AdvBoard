#ifndef SETTINGDIALOGCONTROLLER_H
#define SETTINGDIALOGCONTROLLER_H

#include <QObject>

class SettingDialogController : public QObject
{
    Q_OBJECT
public:
    explicit SettingDialogController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SETTINGDIALOGCONTROLLER_H