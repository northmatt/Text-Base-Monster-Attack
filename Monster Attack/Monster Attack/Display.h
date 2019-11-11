#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>

using std::vector;

class DoubleBuffer {
public:
	DoubleBuffer();

	void WriteBuffer(SHORT x, SHORT y, char* string);
	void FlipBuffer();
	void ClearBuffer();
	void ReleaseBuffer();
private:
	HANDLE hBuffer[2];
	int nBufferIndex;
	SHORT WINDOW_X_SIZE{ 120 };
	SHORT WINDOW_Y_SIZE{ 80 };
};