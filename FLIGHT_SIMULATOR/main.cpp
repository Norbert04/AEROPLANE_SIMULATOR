#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "includes.hpp"
#include "MainWindow.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	ShowWindow(MainWindow::getWindow()->getHWnd(), nCmdShow);



	return 0;
}