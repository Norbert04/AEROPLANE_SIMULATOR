#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "includes.hpp"
#include "MainWindow.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	ShowWindow(MainWindow::getWindow()->getHWnd(), nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}