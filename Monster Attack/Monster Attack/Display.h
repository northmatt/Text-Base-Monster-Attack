#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <gdiplus.h>

using std::vector;
using std::string;
using std::nothrow;
using std::cout;
using std::round;
using std::endl;
using std::to_string;

class DoubleBuffer {
public:
	DoubleBuffer();

	void WriteBuffer(string strInput, double x, double y, int color = 7);
	void DisplayBuffer();
	void loadBackground(WCHAR fileName);
	void ReadBMP(string filename, unsigned char*& imageData, int& width, int& height);
	HANDLE GetConsole() { return hConsole; }
	CONSOLE_SCREEN_BUFFER_INFO GetCSBI() { return csbi; }
	HWND GetHWND() { return wConsole; }
	DWORD GetBufferSize() { return size; }
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