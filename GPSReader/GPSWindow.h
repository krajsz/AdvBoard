#ifndef GPSWINDOW_H
#define GPSWINDOW_H

#include <QMainWindow>
#include "GPSReader.h"
namespace Ui {
class GPSWindow;
}

class QGeoPositionInfo;

class GPSWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit GPSWindow(QWidget *parent = 0);
	~GPSWindow();
private slots:
	void updateInfo(const QGeoPositionInfo& info);

private:
	Ui::GPSWindow *ui;
	GPSReader* m_gpsReader;
};

#endif // GPSWINDOW_H
