#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "BluetoothDataReader.h"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_btDataReader(new BluetoothDataReader)
{
	ui->setupUi(this);

	connect(m_btDataReader, &BluetoothDataReader::newDevice, this, &MainWindow::newBluetoothDevice);
}

void MainWindow::newBluetoothDevice(const QString &name)
{
	ui->btDevicesComboBox->addItem(name);
}

void MainWindow::discoveryError(const QString& error)
{
	ui->errorLabel->setText("Error: " + error);
}

MainWindow::~MainWindow()
{
	delete ui;
}
