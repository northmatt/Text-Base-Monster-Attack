#include "Display.h"
//https://stackoverflow.com/questions/45780650/c-console-application-using-double-buffer-size-limitation
//https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
DoubleBuffer::DoubleBuffer() {
	//was to use to remove flickering but didn't work. props deleting soon
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//Get a handle to the console
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbi);

	WINDOW_X_SIZE = csbi.dwSize.X;
	WINDOW_Y_SIZE = csbi.dwSize.Y;

	COORD size = { WINDOW_X_SIZE , WINDOW_Y_SIZE };
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = WINDOW_X_SIZE - 1;
	rect.Top = 0;
	rect.Bottom = WINDOW_Y_SIZE - 1;

	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, 0, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);
	SetConsoleCursorInfo(hBuffer[0], &cursorinfo);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, 0, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);
	SetConsoleCursorInfo(hBuffer[1], &cursorinfo);

	nBufferIndex = 0;
}

void DoubleBuffer::WriteBuffer(SHORT x, SHORT y, char* string) {
	DWORD dw;
	COORD startposition = { x,y };

	SetConsoleCursorPosition(hBuffer[nBufferIndex], startposition);
	WriteFile(hBuffer[nBufferIndex], string, strlen(string), &dw, NULL);
}

void DoubleBuffer::FlipBuffer() {
	SetConsoleActiveScreenBuffer(hBuffer[nBufferIndex]);
	nBufferIndex = !nBufferIndex;
}

void DoubleBuffer::ClearBuffer() {
	COORD coord = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nBufferIndex], ' ', WINDOW_X_SIZE * WINDOW_Y_SIZE, coord, &dw);
}

void DoubleBuffer::ReleaseBuffer() {
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
