/*



*/
#pragma once
#define LEAN_AND_MEAN

#include <Windows.h>
#include <memory>

class Input;
class Graphics;


class System
{
public:
	System();
	System(const System&);
	~System();

	bool Init();
	void Shutdown();
	int Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	bool InitWindows();
	void ShutdownWindows();

	HWND      m_hWnd            = nullptr;
	HINSTANCE m_hInstance       = nullptr;
	LPCWSTR   m_applicationName = nullptr;
	UINT	  m_clientWidth  = 0;
	UINT	  m_clientHeight = 0;
	DWORD     m_wndStyle     = 0;


	std::unique_ptr<Input>    m_pInput    = nullptr;
	std::unique_ptr<Graphics> m_pGraphics = nullptr;




};


