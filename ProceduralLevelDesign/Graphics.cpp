/*


*/
#include <Windows.h>

#include "Graphics.h"




Graphics::Graphics()
{}



Graphics::Graphics(const Graphics& other)
{}



Graphics::~Graphics()
{}



bool Graphics::Init(int screenWidth, int screenHeigth, HWND hWnd)
{
	return true;
}



void Graphics::Shutdown()
{}



bool Graphics::Frame()
{
	return true;
}



bool Graphics::Render()
{
	return true;
}
