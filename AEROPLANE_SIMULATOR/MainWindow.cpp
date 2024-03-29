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

	if (!IsWindowVisible(hWnd))
		ShowWindow(hWnd, SW_SHOW);

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

	// create swap chain

	//the following code (until the comment marking the end) is edited and licensed under the following license:
	/*The MIT License(MIT)
	Copyright(c) 2024 Norbert Niering
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

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&dxgiSwapChain,
		&device,
		&featureLevel,
		&deviceContext
	);

	device.As(&d3dDevice);
	deviceContext.As(&d3dDeviceContext);

	// render target

	dxgiSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		&backBuffer
	);

	d3dDevice->CreateRenderTargetView(
		backBuffer.Get(),
		nullptr,
		renderTarget.GetAddressOf()
	);

	backBuffer->GetDesc(&backBufferDesc);

	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		static_cast<UINT>(backBufferDesc.Width),
		static_cast<UINT>(backBufferDesc.Height),
		1, 1,
		D3D10_BIND_DEPTH_STENCIL
	);

	d3dDevice->CreateTexture2D(
		&depthStencilDesc,
		nullptr,
		&depthStencilBuffer
	);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

	d3dDevice->CreateDepthStencilView(
		depthStencilBuffer.Get(),
		&depthStencilViewDesc,
		&depthStencilView
	);

	//viewport

	ZeroMemory(&viewport, sizeof(viewport));
	viewport.Height = static_cast<float>(backBufferDesc.Height);
	viewport.Width = static_cast<float>(backBufferDesc.Width);
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	d3dDeviceContext->RSSetViewports(
		1,
		&viewport
	);
	// from here on the license specified in the license file is used
}

void MainWindow::createDeviceDependentResources()
{
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

LRESULT MainWindow::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

HWND MainWindow::getHWnd()
{
	return hWnd;
}

void MainWindow::nextFrame()
{
	dxgiSwapChain->Present(1, 0);
}

MainWindow* MainWindow::window = NULL;

const wchar_t MainWindow::windowClassName[] = L"Main Window";