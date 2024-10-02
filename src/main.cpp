#include <QApplication>
#include <QDebug>
#include <QFontDatabase>

#include "mainWindow.hpp"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	//  NOTE: update this stuff
	QFontDatabase::addApplicationFont(":/res/JuliaMono-Regular.ttf");

	MainWindow mainWindow = MainWindow();
	mainWindow.show();

	return app.exec();
}
