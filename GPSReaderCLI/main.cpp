#include <QCoreApplication>

#include "GPSReader.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	GPSReader reader;

	return a.exec();
}
