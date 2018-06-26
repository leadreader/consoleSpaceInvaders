#pragma once


////////////////////////////////////
//includes
#include <Windows.h>
#include "consoleColor.h"



////////////////////////////////////
//constants
const int screenRows = 25;
const int screenColumns = 80;


///////////////////////////////////
//struct
struct ConsoleSymbolData
{
	char symbol;
	consoleColor symbolColor;
	consoleColor backgroundColor;
};


//////////////////////////////////
//class renderSystem
class renderSystem
{
public:
	renderSystem();

	void initialize();
	void clear();
	void drawChar(int r, int c, char symbol, consoleColor symbolColor, consoleColor backgroundColor);
	void drawText(int r, int c, char* text, consoleColor symbolColor, consoleColor backgroundColor);
	void flush();

private:
	void setConsoleCursor(int r, int c);
	void setConsoleColor(consoleColor symbolColor, consoleColor backgroundColor);

private:
	HANDLE m_consoleHandle;
	ConsoleSymbolData m_backBuffer[screenRows][screenColumns];
	ConsoleSymbolData m_screenBuffer[screenRows][screenColumns];
};