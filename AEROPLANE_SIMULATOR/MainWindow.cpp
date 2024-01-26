#include "MainWindow.hpp"

MainWindow::MainWindow()
{
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
	UnregisterClass(windowClassName, GetModuleHandle(NULL));
	delete window;
	window = NULL;
}

LRESULT MainWindow::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		default:
			return 0;
		}
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

HWND MainWindow::getHWnd()
{
	return hWnd;
}

MainWindow* MainWindow::window = NULL;

const wchar_t MainWindow::windowClassName[] = L"Main Window";