#include "pch.h"
#include <stdio.h>
#include <windows.h>

#define _WIN32_WINNT 0x0500

void setConsoleSize(short x, short y)
{
	char command[15];
	sprintf_s(command, "mode %d,%d", x, y);
	system(command);
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void setCursorPosition(int x, int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}
