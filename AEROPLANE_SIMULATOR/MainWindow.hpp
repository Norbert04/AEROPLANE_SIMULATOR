#pragma once

#include "includes.hpp"
#include "resource.h"

class MainWindow
{
private:
	static const wchar_t windowClassName[];

	Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext;
	Microsoft::WRL::ComPtr<IDXGIDevice4> dxgiDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;

	D3D11_TEXTURE2D_DESC backBufferDesc;

	D3D_FEATURE_LEVEL featureLevel;

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

