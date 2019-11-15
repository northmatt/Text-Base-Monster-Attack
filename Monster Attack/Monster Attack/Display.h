#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <gdiplus.h>

using std::vector;
using std::string;
using std::nothrow;
using std::cout;
using std::round;
using std::endl;

class DoubleBuffer {
public:
	DoubleBuffer();

	void WriteBuffer(string strInput, double x, double y, int color = 7);
	void DisplayBuffer();
	void loadBackground(WCHAR fileName);
	unsigned char* ReadBMP(char* filename);
private:
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND wConsole;

	DWORD size;                      //number of visible characters
	COORD coord = { 0 };               //Top left screen position

	char* writeScreen;
	int* colorScreen;
	bool colorOnFrame{ false };
};