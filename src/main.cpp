#include <QApplication>
#include <QDebug>

#include "mainWindow.hpp"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MainWindow mainWindow = MainWindow();
	mainWindow.show();

	return app.exec();
}
