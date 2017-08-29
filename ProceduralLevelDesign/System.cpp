/*
	use WIN32 00 tutorial


*/
#include "System.h"
#include "Input.h"
#include "Graphics.h"



namespace 
{
	System* g_pSystem = nullptr;
}


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pSystem)
	{
		return g_pSystem->MessageHandler(hWnd, msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}



System::System() : 
	m_pInput(nullptr),
	m_pGraphics(nullptr)
{
	m_applicationName = L"Procedural Level Design";
	m_clientWidth = 800;
	m_clientHeight = 600;
	m_wndStyle = WS_OVERLAPPEDWINDOW;
}



System::System(const System &)
{}



System::~System()
{}



bool System::Init()
{
	InitWindows();

	m_pInput = std::make_unique<Input>();
	if (!m_pInput) return false;
	m_pInput->Init();


	m_pGraphics = std::make_unique<Graphics>();
	if (!m_pGraphics) return false;

	if (!m_pGraphics->Init(m_clientWidth, m_clientHeight, m_hWnd))
	{
		return false;
	}
	
	return true;
}



void System::Shutdown()
{
	if (m_pGraphics) 
		m_pGraphics->Shutdown();

	ShutdownWindows();
}



int System::Run()
{
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		// Handle Windows Messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!Frame())
				break;
		}
	}

	return static_cast<int>(msg.wParam);
}


bool System::Frame()
{
	if (m_pInput->IsKeyDown(VK_ESCAPE))
		return false;

	if (!m_pGraphics->Frame())
		return false;

	return true;
}



bool System::InitWindows()
{
	// Get the instance of the application.
	m_hInstance = GetModuleHandle(NULL);


	WNDCLASSEX wcex = { 0 };
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = m_applicationName;
	wcex.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wcex))
	{
		OutputDebugString(L"\nFailed to create window class\n");
		return false;
	}

	RECT rc = { 0, 0, m_clientWidth, m_clientHeight };
	AdjustWindowRect(&rc, m_wndStyle, FALSE);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// Place the window in the middle of the screeen
	UINT posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	UINT posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	m_hWnd = CreateWindow(m_applicationName,
						  m_applicationName,
						  m_wndStyle,
						  posX, posY,
						  width, height,
						  NULL, NULL,
						  m_hInstance,
						  NULL);

	if(!m_hWnd)
	{
		OutputDebugString(L"\nFailed to create window\n");
		return false;
	}

	// Bring window into focus
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	// Hide the Mouse
	ShowCursor(false);

	return true;
}



void System::ShutdownWindows()
{
	ShowCursor(true);

	// Remove the window
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Remove the application instance
	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
}



LRESULT System::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			m_pInput->KeyDown((unsigned int)wParam);
			break;

		case WM_KEYUP:
			m_pInput->KeyUp((unsigned int)wParam);
			break;

		default:
			DefWindowProc(hWnd, msg, wParam, lParam);
			break;
	}
	return 0;
}
