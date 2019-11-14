#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "Time.h"

using std::vector;
using std::string;
using std::nothrow;
using std::cout;

class DoubleBuffer {
public:
	DoubleBuffer();

	void WriteBuffer(int x, int y, char *input);
	void DisplayBuffer();
private:
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND wConsole;

	DWORD size;                      //number of visible characters
	COORD coord = { 0 };               //Top left screen position

	char* writeScreen;
};