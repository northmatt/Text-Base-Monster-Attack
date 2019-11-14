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
	size_t sizeInput = strlen(input);
	int currentX{ x }, currentY{ y };

	if (currentX >= csbi.dwSize.X || currentY >= csbi.dwSize.Y) {
		string outputChar = "test";
		char* outChar = &outputChar[0];
		WriteBuffer(0, 0, outChar);
		return;
	}

	for (size_t i = 0; i < sizeInput; i++) {
		if (input[i] == '\n') {
			currentX = x;
			currentY++;
		} else {
			if (0 <= currentX && currentX < csbi.dwSize.X && 0 <= currentY && currentY < csbi.dwSize.Y)
				writeScreen[currentX + (csbi.dwSize.X * currentY)] = input[i];
			currentX++;
		}
	}
}

void DoubleBuffer::DisplayBuffer() {
	cout << writeScreen;

	/*if (colors.size() > 1) {
		size_t lastCall{ 0 };
		for (color currentCol : colors) {
			char* p_next_write = &writeScreen[lastCall];
			cout.write(p_next_write, currentCol.start - lastColl - 1)

			//cout << writeScreen[lastCall -> currentCol.start - 1];
			//Change Color
			//cout << writeScreen[currentCol.start -> currentCol.end];
			//Reset color
			//lastCall = currentCol.end + 1
		}

		//cout << writeScreen[lastCall -> size];
	}*/
	
	for (size_t i = 0; i < size - 1; i++) {
		writeScreen[i] = ' ';
	}

	cout.flush();
	SetConsoleCursorPosition(hConsole, coord);
}