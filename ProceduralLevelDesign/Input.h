/*



*/
#pragma once


class Input
{
public:
	Input();
	Input(const Input&);
	~Input();

	void Init();

	void KeyDown(unsigned int input);
	void KeyUp(unsigned int input);
	bool IsKeyDown(unsigned int key);

private:
	bool m_keys[256];
};