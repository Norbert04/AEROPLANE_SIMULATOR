#include "MainWindow.hpp"

MainWindow::MainWindow()
{
	const wchar_t windowClassName[] = L"Main Window";
	
	WNDCLASS windowClass = {};
	windowClass.lpfnWndProc = windowProc;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.lpszClassName = windowClassName;

	RegisterClass(&windowClass);

	hWnd = CreateWindowEx(
		0,
		windowClassName,
		L"flight simulator",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);
}

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

HWND MainWindow::getHWnd()
{
	return hWnd;
}

MainWindow* MainWindow::window = NULL;