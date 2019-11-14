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

	void WriteBuffer(int x, int y, char *input, int color = -1);
	void DisplayBuffer();
private:
	struct color {
		int col;
		size_t start;
		size_t end;
	};

	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND wConsole;

	DWORD size;                      //number of visible characters
	COORD coord = { 0 };               //Top left screen position

	char* writeScreen;

	vector<color> colors;
};