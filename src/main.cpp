#include <QApplication>
#include <QDebug>

#include "mainWindow.hpp"

#include <vectorPair.hpp>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	ss::VectorPair a;

	MainWindow mainWindow = MainWindow();
	mainWindow.show();

	return app.exec();
}
