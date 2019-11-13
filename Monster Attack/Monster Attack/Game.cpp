#include "Game.h"
#include "BattleScene.h"

void Game::InitGame() {
	cout << "Game Init (press 'q' to quit) (use arrow keys) (use 'a' or 'd')\n";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//makes window bigger
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, 1500, 800, true);

	SetConsoleTitle(L"Monster Battle");
	//makes cursor invisible
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorinfo);

	loadedScenes.push_back(new BattleScene());
	loadedScenes.push_back(new BattleScene());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	//cap FPS
	Time::FpsCap();

	//clear the lower portion of the screen
	SetCurPos(0, 2);
	cout << string(10, ' ') + "\n" + string(40, ' ');
	SetCurPos(0, 2);

	currentScene->UpdateScene();

	return (!Input::GetKeyDown('Q'));
}

void Game::SetCurPos(SHORT x, SHORT y) {
	cout.flush();
	COORD theCord = { x, y };
	SetConsoleCursorPosition(hConsole, theCord);
}

void Game::SwitchToScene(int index, bool addFromCurrentScene) {
	if (addFromCurrentScene) {
		currentSceneIndex += index;
		int indSize = static_cast<int>(loadedScenes.size());

		if (currentSceneIndex < 0)
			currentSceneIndex += indSize;
		else if (currentSceneIndex >= indSize)
			currentSceneIndex -= indSize;
	} else
		currentSceneIndex = index;

	currentScene = loadedScenes[currentSceneIndex];
}

/*
static Game *instance() {if (!_inst) _inst = new Game(); return _inst;}
static S& instance() { static S inst; return inst; }
   38
37 40 39
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
}

static char buffer[2048];
char * p_next_write = &buffer[0];
for (int y = 0; y < MAX_Y; y++)
{
	for (int x = 0; x < MAX_X; x++)
	{
		*p_next_write++ = battleField[x][y];
	}
	*p_next_write++ = '\n';
}
*p_next_write = '\0'; // "Insurance" for C-Style strings.
cout.write(&buffer[0], std::distance(p_buffer - &buffer[0]));
*/