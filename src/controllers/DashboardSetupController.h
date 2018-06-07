#ifndef DASHBOARDSETUPCONTROLLER_H
#define DASHBOARDSETUPCONTROLLER_H

#include <QObject>

class DashboardSetupWidget;
class AdvViewController;
class SensorDataReader;

class DashboardSetupController : public QObject
{
     Q_OBJECT
public:
    explicit DashboardSetupController(QObject *parent = nullptr);
    void setSensorDataReader(SensorDataReader* sensorDataReader);
    AdvViewController* viewController();

    void setView(DashboardSetupWidget* const view);
    DashboardSetupWidget* const view() const;
signals:
    void selectDashboardType(int dashboardType);
public slots:
	void startProcessing();

private:
    AdvViewController* m_viewController;
    SensorDataReader* m_sensorDataReader;
    DashboardSetupWidget* m_view;
};

#endif // DASHBOARDSETUPCONTROLLER_H
