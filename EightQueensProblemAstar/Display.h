#pragma once
class Display
{
public:
	Display();
	~Display();

	void printBuffer(std::wstring&);
	void cls();

private:
	HANDLE  hOut;
	DWORD dwMode = 0;

	DWORD written;

	CONSOLE_CURSOR_INFO cursorInfo;
	COORD coord;

	std::wstring buffer;

	void HideCursor();
	void SetZero();
};

