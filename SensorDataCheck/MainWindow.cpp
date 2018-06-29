#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "BluetoothHandler.h"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_bluetoothHandler(new BluetoothHandler)
{
	ui->setupUi(this);

	newDebugString("wtfFFFF");
	connect(m_bluetoothHandler, &BluetoothHandler::debugString, this, &MainWindow::newDebugString);
	connect(m_bluetoothHandler, &BluetoothHandler::messageReceived, this, &MainWindow::messageReceived);
}

void MainWindow::newDebugString(const QString &str)
{
	ui->debugLineEdit->insertPlainText(str + "\n");
}

void MainWindow::messageReceived(const QString &from, const QString &message)
{
	newDebugString(from + ": " + message);
}

MainWindow::~MainWindow()
{
	delete ui;
}
