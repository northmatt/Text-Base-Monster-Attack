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

	/*unsigned char* backgroundRawImage;
	int imageHeight, imageWidth;
	ReadBMP("testImage", backgroundRawImage, imageWidth, imageHeight);

	vector<string> theColorTest;
	vector<int> theColorTest2;
	for (size_t y = 0; y < imageWidth; y++)
		for (size_t x = 0; x < imageHeight; x++) {
			string addedString = "R: " + to_string((int)backgroundRawImage[3 * (y * imageWidth + x)]) + "\tG: " + to_string((int)backgroundRawImage[3 * (y * imageWidth + x) + 1]) + "\tB: " + to_string((int)backgroundRawImage[3 * (y * imageWidth + x) + 2]);

			int theIndex{ -1 };
			if (theColorTest.size() > 1)
				for (size_t i = 0; i < theColorTest.size() - 1; i++)
					if (theColorTest[i] == addedString) {
						theIndex = i;
						break;
					}

			if (theIndex == -1) {
				theColorTest.push_back(addedString);
				theColorTest2.push_back(1);
			} else
				theColorTest2[theIndex] += 1;
		}
	for (size_t i = 0; i < theColorTest.size() - 1; i++)
		cout << theColorTest[i] << "\t  ::  " << theColorTest2[i] << "\n";

	system("pause");*/
}

void DoubleBuffer::WriteBuffer(string strInput, double rawX, double rawY, int col) {
	char* input = &strInput[0];
	size_t sizeInput = strlen(input);
	int x{ static_cast<int>(round(rawX * 2)) }, y{ static_cast<int>(round(rawY)) };
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

		colorOnFrame = false;
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
void DoubleBuffer::ReadBMP(string filename, unsigned char* &imageData, int &width, int &height) {
	/*int i{ 0 };
	FILE* f = fopen(&("backgrounds/" + filename + ".bmp")[0], "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3) {
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	imageData = data;*/
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