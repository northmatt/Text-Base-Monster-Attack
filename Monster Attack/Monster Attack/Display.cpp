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

void DoubleBuffer::WriteBuffer(int x, int y, char *input, int col) {
	size_t sizeInput = strlen(input);
	int currentX{ x }, currentY{ y };
	int colPos{ -1 };

	if (currentX >= csbi.dwSize.X || currentY >= csbi.dwSize.Y) {
		return;
	}

	for (size_t i = 0; i < sizeInput; i++) {
		if (input[i] == '\n') {
			if (col != -1 && colPos >= 0)
				colors[colors.size() - 1].end = static_cast<size_t>(currentX);
			
			currentX = x;
			currentY++;

			colPos = -1;
		} else {
			if (0 <= currentX && currentX < csbi.dwSize.X && 0 <= currentY && currentY < csbi.dwSize.Y) {
				writeScreen[currentX + (csbi.dwSize.X * currentY)] = input[i];
				
				if (col != -1 && colPos == -1) {
					colors.push_back(color{ col, static_cast<size_t>(currentX), static_cast<size_t>(currentX) });
					colPos = currentX;
				} else if (col != -1 && colPos >= 0) {
					colors[colors.size() - 1].end = static_cast<size_t>(currentX);
				}
			} else
				colPos = -1;

			currentX++;
		}
	}
}

void DoubleBuffer::DisplayBuffer() {
	
	if (colors.size() == 0)
		cout << writeScreen;
	else {
		size_t lastCall{ 0 };
		for (color currentCol : colors) {
			//0, 8
			char* p_next_write1 = &writeScreen[lastCall];
			cout.write(p_next_write1, currentCol.start - lastCall);

			SetConsoleTextAttribute(hConsole, currentCol.col);

			char* p_next_write2 = &writeScreen[currentCol.start];
			cout.write(p_next_write2, currentCol.end - currentCol.start);

			SetConsoleTextAttribute(hConsole, 7);

			lastCall = currentCol.end;

			//cout << writeScreen[lastCall -> currentCol.start - 1];
			//Change Color
			//cout << writeScreen[currentCol.start -> currentCol.end];
			//Reset color
			//lastCall = currentCol.end + 1
		}

		char* p_next_write3 = &writeScreen[lastCall];
		cout << p_next_write3;
		//cout << writeScreen[lastCall -> size];

		colors = {};
	}
	
	for (size_t i = 0; i < size - 1; i++) {
		writeScreen[i] = ' ';
	}

	cout.flush();
	SetConsoleCursorPosition(hConsole, coord);
}