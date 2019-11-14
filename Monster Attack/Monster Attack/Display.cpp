#include "Display.h"
//https://stackoverflow.com/questions/45780650/c-console-application-using-double-buffer-size-limitation
//https://stackoverflow.com/questions/34842526/update-console-without-flickering-c

DoubleBuffer::DoubleBuffer() {
	wConsole = GetConsoleWindow();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	//remove scrolling
	COORD new_size =
	{
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(hConsole, new_size);

	//makes window bigger
	system("mode con COLS=700");
	ShowWindow(wConsole, SW_MAXIMIZE);
	SendMessage(wConsole, WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTitle(L"Monster Battle");

	//makes cursor invisible
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorinfo);

	//Find the number of characters to overwrite
	size = csbi.dwSize.X * csbi.dwSize.Y - 8;

	writeScreen = new (nothrow) char[size] { ' ' };
}

void DoubleBuffer::WriteBuffer(int x, int y, char *input) {
	int sizeInput = strlen(input);
	int currentX{ x }, currentY{ y };

	for (int i = 0; i < sizeInput; i++) {
		if (input[i] == '\n') {
			currentX = x;
			currentY++;
		} else if (input[i] != '\0') {
			writeScreen[currentX + (csbi.dwSize.X * currentY)] = input[i];
			currentX++;
		}
	}
}

void DoubleBuffer::DisplayBuffer() {
	cout << writeScreen;
	
	for (size_t i = 0; i < size - 1; i++) {
		writeScreen[i] = ' ';
	}

	cout.flush();
	SetConsoleCursorPosition(hConsole, coord);
}

/*
char* buffer;
buffer = new (nothrow) char[size] { ' ' };

char* p_next_write = &buffer[0];
for (int y = 0; y < csbi.dwSize.Y - 1; y++) {
	for (int x = 0; x < csbi.dwSize.X - 1; x++) {
		*p_next_write++ = writeScreen[x + (csbi.dwSize.X * y)];
	}
	*p_next_write++ = '\n';
}
*p_next_write = '\0'; // "Insurance" for C-Style strings.

buffer = writeScreen;

for (size_t i = 1; i < csbi.dwSize.Y - 1; i++) {
		buffer[csbi.dwSize.X * i - 1] = '\n';
}

cout.write(buffer, size);
*/