#include "Scene.h"

void Scene::UpdateScene() {
//draw background or clear screen
}

/*		to clear screen
void clear_screen ( void )
{
DWORD n;                         //Number of characters written
DWORD size;                      //number of visible characters
COORD coord = { 0 };               //Top left screen position
CONSOLE_SCREEN_BUFFER_INFO csbi;

//Get a handle to the console
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

GetConsoleScreenBufferInfo(h, &csbi);

//Find the number of characters to overwrite
size = csbi.dwSize.X * csbi.dwSize.Y;

//Overwrite the screen buffer with whitespace
FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
GetConsoleScreenBufferInfo(h, &csbi);
FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

//Reset the cursor to the top left position
SetConsoleCursorPosition(h, coord);
}*/