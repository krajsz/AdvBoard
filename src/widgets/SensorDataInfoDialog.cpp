/***************************************************************************
File		: SensorDataInfoDialog.cpp
Project		: AdvBoard
Description	: Dialog for accessing the loaded sensor data
--------------------------------------------------------------------
Copyright   : (C) 2018 Fabian Kristof (fkristofszabolcs@gmail.com)
***************************************************************************/
#include "SensorDataInfoDialog.h"
#include "ui_sensordatainfodialog.h"
#include "src/sensors/AccelerationSensor.h"

#include <QTreeWidgetItem>
#include <QVector>

#include <QDebug>
SensorDataInfoDialog::SensorDataInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorDataInfoDialog)
{
    ui->setupUi(this);
}

SensorDataInfoDialog::~SensorDataInfoDialog()
{
    delete ui;
}

void SensorDataInfoDialog::setSensors(const QVector<QJsonObject>&sensorData)
{
    ui->sensorDataTreeView->clear();
	QVector<AbstractSensor*> sensors;

	for (const QJsonObject& data : sensorData)
	{
		sensors.push_back(SensorDataReader::sensorFromData(data));
	}

	qDebug() <<"sensors size: " << sensors.size();
	for (AbstractSensor* sensor : sensors)
    {
        QTreeWidgetItem* sensorTreeItem = new QTreeWidgetItem;
        QTreeWidgetItem* sensorDataNameTreeItem;;
        QTreeWidgetItem* sensorValueTreeItem;

        if (sensor->type() == AbstractSensor::SensorType::AccelerationSensor)
        {
            AccelerationSensor* accsensor = qobject_cast<AccelerationSensor*>(sensor);
            sensorTreeItem->setText(0, "Acceleration");
            sensorTreeItem->setIcon(0, QIcon(":/pictures/data/gsensorIcon.png"));
            //ID
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "ID");
            //ID Value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(accsensor->id()));
            sensorDataNameTreeItem->addChild(sensorValueTreeItem);

            sensorTreeItem->addChild(sensorDataNameTreeItem);

            //Value
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "Value");

            //x min
            QTreeWidgetItem* accelerationBoundariesItem = new QTreeWidgetItem;
            accelerationBoundariesItem->setText(0, "X Min");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(accsensor->xMinAcceleration(),'f', 2));

            accelerationBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(accelerationBoundariesItem);

            //x max
            accelerationBoundariesItem = new QTreeWidgetItem;
            accelerationBoundariesItem->setText(0, "X Max");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(accsensor->xMaxAcceleration(),'f', 2));

            accelerationBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(accelerationBoundariesItem);

            //y min
            accelerationBoundariesItem = new QTreeWidgetItem;
            accelerationBoundariesItem->setText(0, "Y Min");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(accsensor->yMinAcceleration(),'f', 2));

            accelerationBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(accelerationBoundariesItem);

            //y max
            accelerationBoundariesItem = new QTreeWidgetItem;
            accelerationBoundariesItem->setText(0, "Y Max");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(accsensor->yMaxAcceleration(),'f', 2));\

            accelerationBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(accelerationBoundariesItem);
            //Value
            accelerationBoundariesItem = new QTreeWidgetItem;
            accelerationBoundariesItem->setText(0, "Current");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            const QPointF& accValue = accsensor->value().toPointF();

            const QString& valueText = QLatin1String("(") + QString::number(accValue.x(), 'f', 2) +
                                       QLatin1String(", ")+ QString::number(accValue.y(), 'f', 2) +
                                       QLatin1String(")");

            sensorValueTreeItem->setText(0, valueText);

            accelerationBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(accelerationBoundariesItem);

            accelerationBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(accelerationBoundariesItem);
            sensorTreeItem->addChild(sensorDataNameTreeItem);
        }
        else if (sensor->type() == AbstractSensor::SensorType::GPSpositionSensor)
        {
            sensorTreeItem->setText(0, "GPS position");
            sensorTreeItem->setIcon(0, QIcon(":/pictures/data/gpsSensorIcon.png"));


        }
        else if (sensor->type() == AbstractSensor::SensorType::HumiditySensor)
        {
            sensorTreeItem->setText(0, "Humidity");
            sensorTreeItem->setIcon(0, QIcon(":/pictures/data/humiditySensorIcon.png"));

            //ID
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "ID");
            //ID Value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->id()));
            sensorDataNameTreeItem->addChild(sensorValueTreeItem);

            sensorTreeItem->addChild(sensorDataNameTreeItem);

            //Value
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "Value");

            //min humidity
            QTreeWidgetItem* humidityBoundariesItem = new QTreeWidgetItem;
            humidityBoundariesItem->setText(0, "Min humidity");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->minValue().toDouble(),'f', 2));

            humidityBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(humidityBoundariesItem);
            //max humidity
            humidityBoundariesItem = new QTreeWidgetItem;
            humidityBoundariesItem->setText(0, "Max humidity");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->maxValue().toDouble(),'f', 2));

            humidityBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(humidityBoundariesItem);
            //current humidity
            humidityBoundariesItem = new QTreeWidgetItem;
            humidityBoundariesItem->setText(0, "Current");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->value().toDouble(),'f', 2));

            humidityBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(humidityBoundariesItem);
            sensorTreeItem->addChild(sensorDataNameTreeItem);
        }
        else if (sensor->type() == AbstractSensor::SensorType::SpeedSensor)
        {
            sensorTreeItem->setText(0, "Speed");
            sensorTreeItem->setIcon(0, QIcon(":/pictures/data/speedSensorIcon.png"));

            //ID
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "ID");
            //ID Value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->id()));
            sensorDataNameTreeItem->addChild(sensorValueTreeItem);

            sensorTreeItem->addChild(sensorDataNameTreeItem);

            //Value
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "Value");

            //max speed
            QTreeWidgetItem* speedValuesItem = new QTreeWidgetItem;
            speedValuesItem->setText(0, "Max speed");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->maxValue().toInt(),'f', 2));

            speedValuesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(speedValuesItem);
            //current speed
            speedValuesItem = new QTreeWidgetItem;
            speedValuesItem->setText(0, "Current");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->value().toInt(),'f', 2));

            speedValuesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(speedValuesItem);

            sensorTreeItem->addChild(sensorDataNameTreeItem);
        }
        else if (sensor->type() == AbstractSensor::SensorType::TemperatureSensor)
        {
            sensorTreeItem->setText(0, "Temperature");
            sensorTreeItem->setIcon(0, QIcon(":/pictures/data/tempSensorIcon.png"));

            //ID
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "ID");
            //ID Value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->id()));
            sensorDataNameTreeItem->addChild(sensorValueTreeItem);

            sensorTreeItem->addChild(sensorDataNameTreeItem);

            //Value
            sensorDataNameTreeItem = new QTreeWidgetItem;
            sensorDataNameTreeItem->setText(0, "Value");

            //min temp
            QTreeWidgetItem* tempBoundariesItem = new QTreeWidgetItem;
            tempBoundariesItem->setText(0, "Min temp");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->minValue().toDouble(),'f', 2));

            tempBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(tempBoundariesItem);
            //max temp
            tempBoundariesItem = new QTreeWidgetItem;
            tempBoundariesItem->setText(0, "Max temp");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->maxValue().toDouble(),'f', 2));

            tempBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(tempBoundariesItem);
            //current temp
            tempBoundariesItem = new QTreeWidgetItem;
            tempBoundariesItem->setText(0, "Current");

            //Value value
            sensorValueTreeItem = new QTreeWidgetItem;
            sensorValueTreeItem->setText(0, QString::number(sensor->value().toDouble(),'f', 2));

            tempBoundariesItem->addChild(sensorValueTreeItem);
            sensorDataNameTreeItem->addChild(tempBoundariesItem);

            sensorTreeItem->addChild(sensorDataNameTreeItem);
        }

        if (sensorTreeItem)
            ui->sensorDataTreeView->addTopLevelItem(sensorTreeItem);

	}
	show();
}
