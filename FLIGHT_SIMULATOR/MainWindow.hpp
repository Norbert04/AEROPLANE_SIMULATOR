#pragma once

#include "includes.hpp"

class MainWindow
{
private:
	HWND hWnd;

	MainWindow(HWND hWnd);

	static MainWindow* window;

public:
	MainWindow(const MainWindow&) = delete;
	void operator=(const MainWindow&) = delete;

	static MainWindow* getWindow();
	static void deleteWindow();
};

