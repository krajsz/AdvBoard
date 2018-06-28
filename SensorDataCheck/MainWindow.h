#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class BluetoothHandler;
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void newDebugString(const QString& str);
	void messageReceived(const QString& from, const QString& message);
private:
	BluetoothHandler* m_bluetoothHandler;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
