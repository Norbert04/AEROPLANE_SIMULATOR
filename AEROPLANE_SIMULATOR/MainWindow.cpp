#include "MainWindow.hpp"

MainWindow::MainWindow()
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS windowClass = {};
	windowClass.lpfnWndProc = windowProc;
	windowClass.hInstance = hInst;
	windowClass.lpszClassName = windowClassName;
	windowClass.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));

	RegisterClass(&windowClass);

	hWnd = CreateWindowEx(
		0,
		windowClassName,
		L"aeroplane simulator",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
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

const D3D_FEATURE_LEVEL MainWindow::levels[] = {
	D3D_FEATURE_LEVEL_12_2,
	D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
};