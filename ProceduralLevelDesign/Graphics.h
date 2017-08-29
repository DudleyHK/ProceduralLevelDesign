/*



*/
#pragma once


class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Init(int screenWidth, int screenHeight, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.f;
	const float SCREEN_NEAR = 0.1f;
};