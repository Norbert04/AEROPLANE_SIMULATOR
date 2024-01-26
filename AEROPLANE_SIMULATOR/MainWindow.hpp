#pragma once

#include "includes.hpp"

class MainWindow
{
private:
	static const wchar_t windowClassName[];

	HWND hWnd;

	MainWindow();

	static MainWindow* window;

public:
	MainWindow(const MainWindow&) = delete;
	void operator=(const MainWindow&) = delete;

	static MainWindow* getWindow();
	static void deleteWindow();

	static LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND getHWnd();
};

