#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "Time.h"

using std::vector;
using std::string;

class DoubleBuffer {
public:
	DoubleBuffer();

	void WriteBuffer(SHORT x, SHORT y, char *string);
	void DisplayBuffer();
private:
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND wConsole;
	SHORT WINDOW_X_SIZE{ 0 };
	SHORT WINDOW_Y_SIZE{ 0 };

	DWORD n;                         //Number of characters written
	DWORD size;                      //number of visible characters
	COORD coord = { 0 };               //Top left screen position

	HANDLE hBuffer[2];
	int nBufferIndex{ 0 };
};