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

	RECT resSize;
	GetWindowRect(wConsole, &resSize);
	SetCursorPos(resSize.right / 2, resSize.bottom);

	writeScreen = new (nothrow) char[size] { ' ' };
	colorScreen = new (nothrow) int[size] { 7 };
}

void DoubleBuffer::WriteBuffer(string strInput, double rawX, double rawY, int col) {
	char* input = &strInput[0];
	size_t sizeInput = strlen(input);
	int x{ static_cast<int>(round(rawX)) }, y{ static_cast<int>(round(rawY)) };
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
				writeScreen[currentX + (csbi.dwSize.X * currentY)] = input[i];
				colorScreen[currentX + (csbi.dwSize.X * currentY)] = col;

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
		for (size_t i = 0; i < size; i++)
			if (colorScreen[i] != intColor || i == size - 1) {
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
		for (size_t i = 0; i < size - 1; i++)
			colorScreen[i] = 7;
	}
	
	//clear text buffer
	for (size_t i = 0; i < size - 1; i++)
		writeScreen[i] = ' ';

	//clear the actual built-in cout buffer and reset cursor pos
	cout.flush();
	SetConsoleCursorPosition(hConsole, coord);
}

void DoubleBuffer::loadBackground(WCHAR fileName) {
	//loadBackground(L"level_one.png")
	/*static Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	static ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HBITMAP result = NULL;

	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(fileName, false);
	bitmap->GetHBITMAP(NULL, &result);
	delete bitmap;

	//read image and load into map from "result"

	Gdiplus::GdiplusShutdown(gdiplusToken);*/
}
//https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file/38440684
unsigned char* DoubleBuffer::ReadBMP(char* filename) {
	int i{ 0 };
	//FILE* f = fopen(filename, "rb");
	FILE* f = NULL;

	if (f == NULL)
		throw "Argument Exception";

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	cout << std::endl;
	cout << "  Name: " << filename << endl;
	cout << " Width: " << width << endl;
	cout << "Height: " << height << endl;

	int row_padded = (width * 3 + 3) & (~3);
	unsigned char* data = new unsigned char[row_padded];
	unsigned char tmp;

	for (int i = 0; i < height; i++) {
		fread(data, sizeof(unsigned char), row_padded, f);
		for (int j = 0; j < width * 3; j += 3) {
			// Convert (B, G, R) to (R, G, B)
			tmp = data[j];
			data[j] = data[j + 2];
			data[j + 2] = tmp;

			cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
		}
	}

	fclose(f);
	return data;
}

/*
https://stackoverflow.com/questions/1918263/reading-pixels-of-image-in-c
#include <Magick++.h>
#include <iostream>

using namespace Magick;
using namespace std;

int main(int argc, char **argv) {
 try {
  InitializeMagick(*argv);
  Image img("C:/test.bmp");
  ColorRGB rgb(img.pixelColor(0, 0));  // ie. pixel at pos x=0, y=0
  cout << "red: " << rgb.red();
  cout << ", green: " << rgb.green();
  cout << ", blue: " << rgb.blue() << endl;
 }
  catch ( Magick::Exception & error) {
  cerr << "Caught Magick++ exception: " << error.what() << endl;
 }
 return 0;
}
*/