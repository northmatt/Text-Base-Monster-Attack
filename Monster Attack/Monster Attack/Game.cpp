#include "Game.h"
#include "BattleScene.h"

void Game::InitGame() {
	cout << "Game Init (press 'q' to quit) (use arrow keys) (use 'a' or 'd')\n";

	loadedScenes.push_back(new BattleScene());
	loadedScenes.push_back(new BattleScene());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	//cap FPS
	Time::FpsCap();

	currentScene->UpdateScene();

	buffer.DisplayBuffer();

	return (!Input::GetKeyDown('Q'));
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
*/