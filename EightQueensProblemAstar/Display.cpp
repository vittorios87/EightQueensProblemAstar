#include "pch.h"
#include "Display.h"


Display::Display() : hOut(GetStdHandle(STD_OUTPUT_HANDLE))
{

	if (!GetConsoleMode(hOut, &dwMode))
	{
		//std::cout << GetLastError();
		return;
	}
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	SetConsoleCP(0);
	SetConsoleOutputCP(0);
	std::ios_base::sync_with_stdio(false);


	HideCursor();


	SetZero();

}
Display::~Display()
{
}

void Display::HideCursor()
{
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);
}
void Display::SetZero() {

	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(hOut, coord);
}

void Display::printBuffer(std::wstring& inputBuffer) {
	/* NON FUNZIONANTE*/
	/*
	if (inputBuffer.size() < buffer.size() ){
		int sizeDiff = buffer.size() - inputBuffer.size();
		while (sizeDiff > 0) {
			inputBuffer.append(L" ");
			sizeDiff--;
		}
	}
	*/
	//cls();
	HideCursor();
	SetZero();
	WriteConsole(hOut, inputBuffer.c_str(), inputBuffer.size(), &written, NULL);
}

void Display::cls()
{
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hOut, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.
	FillConsoleOutputCharacter(hOut,        // Handle to console screen buffer 
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coord,     // Coordinates of first cell 
		&cCharsWritten);// Receive number of characters written

	GetConsoleScreenBufferInfo(hOut, &csbi);
	FillConsoleOutputAttribute(hOut,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coord,      // Coordinates of first cell 
		&cCharsWritten); // Receive number of characters written
	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hOut, coord);
}