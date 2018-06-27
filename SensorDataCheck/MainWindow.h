#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class BluetoothDataReader;

#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void newBluetoothDevice(const QString& name);
	void discoveryError(const QString& error);
private:
	BluetoothDataReader* m_btDataReader;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
