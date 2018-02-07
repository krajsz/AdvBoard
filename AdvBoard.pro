#-------------------------------------------------
#
# Project created by QtCreator 2018-01-22T15:38:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AdvBoard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += multimedia multimediawidgets
CONFIG += c++14
SOURCES += \
        src/main.cpp \
        src/AdvBoardMain.cpp \
    src/controllers/AdvMainController.cpp \
    src/controllers/SensorDataValidatingDialogController.cpp \
    src/controllers/VideoInfoDialogController.cpp \
    src/controllers/SensorDataInfoDialogController.cpp \
    src/controllers/AdvViewController.cpp \
    src/dashboards/AbstractDashboard.cpp \
    src/dashboards/MotorcycleDashboard.cpp \
    src/datasources/VideoSource.cpp \
    src/datasources/LiveVideoSource.cpp \
    src/datasources/SensorDataReader.cpp \
    src/datasources/LiveSensorDataReader.cpp \
    src/widgets/SensorDataValidatingDialog.cpp \
    src/widgets/VideoInfoDialog.cpp \
    src/widgets/SensorDataInfoDialog.cpp \
    src/widgets/SettingDialog.cpp \
    src/sensors/AbstractSensor.cpp \
    src/sensors/TemperatureSensor.cpp \
    src/view/AdvVideoView.cpp \
    src/view/AdvSensorItem.cpp \
    src/view/AdvVideoScene.cpp \
    src/VideoRecorder.cpp \
    src/controllers/SettingDialogController.cpp \
    src/widgets/VideoLoadingDialog.cpp \
    src/sensors/HumiditySensor.cpp \
    src/sensors/SpeedSensor.cpp \
    src/sensors/AccelerationSensor.cpp \
    src/sensors/GPSpositionSensor.cpp \
    src/dashboards/HikerDashboard.cpp \
    src/dashboards/BikerDashboard.cpp \
    src/widgets/SelectProcessingModeWidget.cpp \
    src/widgets/LiveProcessingSetupWidget.cpp \
    src/widgets/PostProcessingSetupWidget.cpp \
    src/widgets/DashboardSetupWidget.cpp \
    src/widgets/PreviewWidget.cpp \
    src/widgets/ValidationErrorsDialog.cpp \
    src/datasources/validators/SensorDataSourceValidator.cpp \
    src/datasources/validators/SensorValidator.cpp \
    src/datasources/validators/GPSSensorValidator.cpp \
    src/datasources/validators/SpeedSensorValidator.cpp \
    src/datasources/validators/AccelerationSensorValidator.cpp \
    src/datasources/validators/HumiditySensorValidator.cpp \
    src/datasources/validators/TemperatureSensorValidator.cpp \
    src/datasources/validators/DashboardTypeValidator.cpp \
    src/datasources/validators/SensorTypeValidator.cpp

HEADERS += \
        src\AdvBoardMain.h \
    src/controllers/AdvViewController.h \
    src/controllers/AdvMainController.h \
    src/controllers/VideoInfoDialogController.h \
    src/controllers/SensorDataInfoDialogController.h \
    src/controllers/SensorDataValidatingDialogController.h \
    src/dashboards/AbstractDashboard.h \
    src/dashboards/MotorcycleDashboard.h \
    src/datasources/VideoSource.h \
    src/datasources/LiveVideoSource.h \
    src/datasources/SensorDataReader.h \
    src/datasources/LiveSensorDataReader.h \
    src/widgets/VideoInfoDialog.h \
    src/widgets/SensorDataInfoDialog.h \
    src/widgets/SensorDataValidatingDialog.h \
    src/widgets/SettingDialog.h \
    src/sensors/TemperatureSensor.h \
    src/sensors/AbstractSensor.h \
    src/view/AdvVideoView.h \
    src/view/AdvSensorItem.h \
    src/view/AdvVideoScene.h \
    src/VideoRecorder.h \
    src/controllers/SettingDialogController.h \
    src/widgets/VideoLoadingDialog.h \
    src/sensors/HumiditySensor.h \
    src/sensors/SpeedSensor.h \
    src/sensors/AccelerationSensor.h \
    src/sensors/GPSpositionSensor.h \
    src/dashboards/HikerDashboard.h \
    src/dashboards/BikerDashboard.h \
    src/widgets/SelectProcessingModeWidget.h \
    src/widgets/LiveProcessingSetupWidget.h \
    src/widgets/PostProcessingSetupWidget.h \
    src/widgets/DashboardSetupWidget.h \
    src/widgets/PreviewWidget.h \
    src/widgets/ValidationErrorsDialog.h \
    src/datasources/validators/SensorDataSourceValidator.h \
    src/datasources/validators/SensorValidator.h \
    src/datasources/validators/GPSSensorValidator.h \
    src/datasources/validators/SpeedSensorValidator.h \
    src/datasources/validators/AccelerationSensorValidator.h \
    src/datasources/validators/HumiditySensorValidator.h \
    src/datasources/validators/TemperatureSensorValidator.h \
    src/datasources/validators/DashboardTypeValidator.h \
    src/datasources/validators/SensorTypeValidator.h

FORMS += \
        src/ui\advboardmain.ui \
    src/ui/sensordatavalidatingdialog.ui \
    src/ui/videoinfodialog.ui \
    src/ui/sensordatainfodialog.ui \
    src/ui/settingdialog.ui \
    src/ui/videoloadingdialog.ui \
    src/ui/selectprocessingmodewidget.ui \
    src/ui/liveprocessingsetupwidget.ui \
    src/ui/postprocessingsetupwidget.ui \
    src/ui/dashboardsetupwidget.ui \
    src/ui/previewwidget.ui \
    src/ui/validationerrorsdialog.ui

RESOURCES +=\
    src/resources.qrc

DISTFILES += \
    src/scripts/tcpData.py
