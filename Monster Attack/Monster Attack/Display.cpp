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
	size = csbi.dwSize.X * csbi.dwSize.Y;

	RECT resSize;
	GetWindowRect(wConsole, &resSize);
	SetCursorPos(resSize.right / 2, resSize.bottom);

	writeScreen = new (nothrow) char[size + 1] { ' ' };
	colorScreen = new (nothrow) int[size] { 7 };

	camPosOffset[0] = csbi.dwSize.X / 2;
	camPosOffset[1] = csbi.dwSize.Y / 2;
}

void DoubleBuffer::WriteBuffer(string strInput, double rawX, double rawY, int col, bool mergeCol, bool isUI) {
	char* input = &strInput[0];
	size_t sizeInput = strlen(input);

	int x{ 0 }, y{ 0 };
	if (isUI) {
		x = static_cast<int>(round(rawX * 2));
		y = static_cast<int>(round(rawY));
	}
	else {
		x = static_cast<int>(round(rawX * 2)) - camPos[0];
		y = static_cast<int>(round(rawY)) - camPos[1];
	}
	
	int currentX{ x }, currentY{ y };

	//check if image is offscreen
	if (currentX >= csbi.dwSize.X || currentY >= csbi.dwSize.Y)
		return;

	//write the image given into the 1D buffer array.
	for (size_t i = 0; i < sizeInput; i++) {
		if (input[i] == '\n') {
			currentX = x;
			currentY++;
		} else {
			//check if character is offscreen
			if (0 <= currentX && currentX < csbi.dwSize.X && 0 <= currentY && currentY < csbi.dwSize.Y) {
				int theIndex{ currentX + (csbi.dwSize.X * currentY) };
				writeScreen[theIndex] = input[i];

				if (mergeCol && colorScreen[theIndex] != 7)
					colorScreen[theIndex] |= col;
				else
					colorScreen[theIndex] = col;

				if (col != 7)
					colorOnFrame = true;
			}

			currentX++;
		}
	}
}

void DoubleBuffer::DisplayBuffer() {
	if (!colorOnFrame)
		cout << writeScreen;
	else {
		//looks at the colors in the list which contain starting and ending index. Draw all characters in batches to reduce the couts as much as possible as it's slow
		size_t lastCall{ 0 };
		int intColor{ 7 };
		for (size_t i = 0; i <= size; i++)
			if (colorScreen[i] != intColor || i == size) {
				//change color
				SetConsoleTextAttribute(hConsole, intColor);

				//draw the buffer starting from its last call to its current position
				char* p_next_write1 = &writeScreen[lastCall];
				cout.write(p_next_write1, i - lastCall);

				intColor = colorScreen[i];
				lastCall = i;
			}
		//reset color
		SetConsoleTextAttribute(hConsole, 7);

		//clear color buffer
		for (size_t i = 0; i < size; i++)
			colorScreen[i] = 7;

		colorOnFrame = false;
	}
	
	//clear text buffer
	for (size_t i = 0; i < size; i++)
		writeScreen[i] = ' ';

	//clear the actual built-in cout buffer and reset cursor pos
	cout.flush();
	SetConsoleCursorPosition(hConsole, coord);
}

void DoubleBuffer::DisplayBackground(vector<char> writeBack, vector<vector<int>> rectInp) {
	vector<int> backPos;
	backPos = { rectInp[0][0] - camPos[0], rectInp[0][1] - camPos[1] };

	vector<vector<int>> rectBack;
	rectBack.push_back(vector<int>{ max(0, backPos[0]), max(0, backPos[1]) });
	rectBack.push_back(vector<int>{ min(rectInp[1][0] + backPos[0], csbi.dwSize.X), min(rectInp[1][1] + backPos[1], csbi.dwSize.Y) });

	for (size_t y = rectBack[0][1]; y < rectBack[1][1]; y++)
		for (size_t x = rectBack[0][0]; x < rectBack[1][0]; x++)
			writeScreen[x + y * csbi.dwSize.X] = writeBack[x - backPos[0] + (y - backPos[1]) * rectInp[1][0]];
}

void DoubleBuffer::DisplayBackground(vector<char> writeBack, vector<int> colorBack, vector<vector<int>> rectInp) {
	vector<int> backPos;
	backPos = { rectInp[0][0] - camPos[0], rectInp[0][1] - camPos[1] };
	
	vector<vector<int>> rectBack;
	rectBack.push_back(vector<int>{ max(0, backPos[0]), max(0, backPos[1]) });
	rectBack.push_back(vector<int>{ min(rectInp[1][0] + backPos[0], csbi.dwSize.X), min(rectInp[1][1] + backPos[1], csbi.dwSize.Y) });

	for (size_t y = rectBack[0][1]; y < rectBack[1][1]; y++)
		for (size_t x = rectBack[0][0]; x < rectBack[1][0]; x++) {
			writeScreen[x + y * csbi.dwSize.X] = writeBack[x - backPos[0] + (y - backPos[1]) * rectInp[1][0]];
			colorScreen[x + y * csbi.dwSize.X] = colorBack[x - backPos[0] + (y - backPos[1]) * rectInp[1][0]];
		}

	colorOnFrame = true;
}

void DoubleBuffer::SetCamPos(vector<int> pos) {
	camPos = { pos[0] * 2 - camPosOffset[0], pos[1] - camPosOffset[1] };

	if (camPos[0] < camMaxValue[0][0])
		camPos[0] = camMaxValue[0][0];
	else if (camPos[0] + csbi.dwSize.X > camMaxValue[1][0])
		camPos[0] = max(camMaxValue[1][0] - csbi.dwSize.X, camMaxValue[0][0]);

	if (camPos[1] < camMaxValue[0][1])
		camPos[1] = camMaxValue[0][1];
	else if (camPos[1] + csbi.dwSize.Y > camMaxValue[1][1])
		camPos[1] = max(camMaxValue[1][1] - csbi.dwSize.Y, camMaxValue[0][1]);
}

void DoubleBuffer::SetMaxCam(vector<int> inputMaxP1, vector<int> inputMaxP2) {
	camMaxValue = {inputMaxP1, inputMaxP2};
}

void DoubleBuffer::SetCurPos(SHORT x, SHORT y) {
	cout.flush();
	COORD cord{x, y};
	SetConsoleCursorPosition(hConsole, cord);
}
