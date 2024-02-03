#include "MainWindow.hpp"

MainWindow::MainWindow()
{
	// create window

	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS windowClass = {};
	windowClass.lpfnWndProc = windowProc;
	windowClass.hInstance = hInst;
	windowClass.lpszClassName = windowClassName;
	windowClass.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

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

	// create device

	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG) || defined(DEBUG)
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // defined(_DEBUG) || defined(DEBUG)

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

	D3D_FEATURE_LEVEL featureLevels[] = {
	D3D_FEATURE_LEVEL_12_2,
	D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	};

	D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&device,
		&featureLevel,
		&deviceContext
	);

	device.As(&d3dDevice);
	deviceContext.As(&d3dDeviceContext);

	// create swap chain

	//the following code (until the comment marking the end) is edited and licensed under the following license:
	/*The MIT License(MIT)
	Copyright(c) Microsoft Corporation

	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
	associated documentation files(the "Software"), to deal in the Software without restriction,
	including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions :

	The above copyright notice and this permission notice shall be included in all copies or substantial
	portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
	NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

	Microsoft::WRL::ComPtr<IDXGIDevice4> deviceDXGI;
	d3dDevice.As(&deviceDXGI);

	Microsoft::WRL::ComPtr<IDXGIFactory> factory;
	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;

	if (SUCCEEDED(deviceDXGI->GetAdapter(&adapter)))
	{
		adapter->GetParent(IID_PPV_ARGS(&factory));

		factory->CreateSwapChain(
			d3dDevice.Get(),
			&swapChainDesc,
			&dxgiSwapChain
		);
	}
	// from here on the license specified in the license file is used
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