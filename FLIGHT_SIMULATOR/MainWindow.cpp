#include "MainWindow.hpp"

MainWindow* MainWindow::getWindow()
{
	if (window == NULL)
		window = new MainWindow();

	return window;
}

void MainWindow::deleteWindow()
{
	delete window;
	window = NULL;
}

LRESULT MainWindow::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

MainWindow* MainWindow::window = NULL;