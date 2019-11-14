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

	SetConsoleTitle(L"Monster Battle");

	//makes cursor invisible
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorinfo);

	//Find the number of characters to overwrite
	size = csbi.dwSize.X * csbi.dwSize.Y;

	COORD rectCords = { csbi.dwSize.X, csbi.dwSize.Y };
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = rectCords.X - 1;
	rect.Top = 0;
	rect.Bottom = rectCords.Y - 1;

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], rectCords);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);
	SetConsoleCursorInfo(hBuffer[0], &cursorinfo);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], rectCords);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);
	SetConsoleCursorInfo(hBuffer[1], &cursorinfo);
}

void DoubleBuffer::WriteBuffer(SHORT x, SHORT y, char *string) {
	COORD startposition = { x,y };

	SetConsoleCursorPosition(hBuffer[nBufferIndex], startposition);
	WriteFile(hBuffer[nBufferIndex], string, strlen(string), &n, NULL);
}

void DoubleBuffer::DisplayBuffer() {
	SetConsoleActiveScreenBuffer(hBuffer[nBufferIndex]);
	nBufferIndex = !nBufferIndex;
	FillConsoleOutputCharacter(hBuffer[nBufferIndex], TEXT(' '), size, coord, &n);
}

/*
static char buffer[2048];
char *p_next_write = &buffer[0];
for (int y = 0; y < MAX_Y; y++) {
	for (int x = 0; x < MAX_X; x++) {
		*p_next_write++ = battleField[x][y];
	}
	*p_next_write++ = '\n';
}
*p_next_write = '\0'; // "Insurance" for C-Style strings.
cout.write(&buffer[0], std::distance(p_buffer - &buffer[0]));
*/