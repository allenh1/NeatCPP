#include <QApplication>
#include <QtWidgets>

#include "MainWindow.h"

int main (int argc, char ** argv)
{
	QApplication app(argc, argv);

	MainWindow * pMain = new MainWindow();
	pMain->show();

	return app.exec();
}