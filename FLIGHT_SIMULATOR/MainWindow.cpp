#include "MainWindow.hpp"

MainWindow* MainWindow::getWindow()
{
	if (window == NULL)
		window = new MainWindow(0); // TODO: create real window
		window = new MainWindow(); // TODO: create real window

	return window;
}

void MainWindow::deleteWindow()
{
	// TODO: properly close window
	delete window;
	window = NULL;
}

MainWindow* MainWindow::window = NULL;