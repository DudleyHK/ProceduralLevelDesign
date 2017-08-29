/*



*/
#include "System.h"


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow)
{
	std::unique_ptr<System> m_pSystem = std::make_unique<System>();
	if (!m_pSystem)
	{
		OutputDebugStringA("Error: m_pSystem returned null");
		return 0;
	}

	if(m_pSystem->Init())
	{
		m_pSystem->Run();
	}

	m_pSystem->Shutdown();
	return 0;
}