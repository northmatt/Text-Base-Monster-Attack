#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <gdiplus.h>
#include "Vectors.h"

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
	void DisplayBackground(vector<char> writeBack, vector<vector<int>> rectInp);
	void DisplayBackground(vector<char> writeBack, vector<int> colorBack, vector<vector<int>> rectBack);
	void SetCamPos(vector<int> pos);
	void SetMaxCam(vector<int> inputMaxP1, vector<int> inputMaxP2);
	
	HANDLE GetConsole() { return hConsole; }
	CONSOLE_SCREEN_BUFFER_INFO GetCSBI() { return csbi; }
	HWND GetHWND() { return wConsole; }
	DWORD GetBufferSize() { return size; }
	vector<int> GetCamPos() { return camPos; }
private:
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND wConsole;

	DWORD size;                      //number of visible characters
	COORD coord = { 0 };               //Top left screen position

	char* writeScreen;
	int* colorScreen;
	bool colorOnFrame{ false };

	vector<int> camPos{ 0, 0 };
	vector<int> camPosOffset{ 0, 0 };
	vector<vector<int>> camMaxValue{ {0, 0}, {1, 1} };
};