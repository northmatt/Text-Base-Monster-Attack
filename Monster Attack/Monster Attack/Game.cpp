#include "Game.h"
#include "BattleScene.h"
#include "MapCreator.h"
#include "MapLevel.h"
#include "Titlescreen.h"
#include "Pausescreen.h"

void Game::InitGame() {
	cout << "Game Init (press 'q' to quit) (use arrow keys) (use 'a' or 'd')\n";

	loadedScenes.push_back(new Titlescreen());
	loadedScenes.push_back(new Pausescreen());
	loadedScenes.push_back(new BattleScene());
	loadedScenes.push_back(new MapLevel());
	//loadedScenes.push_back(new MapCreator());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	//cap FPS
	Time::FpsCap();

	Input::updateInps();

	isRunning = !Input::GetKeyDown(VK_F4);

	currentScene->UpdateScene();

	buffer.DisplayBuffer();

	return isRunning;
}

void Game::SwitchToScene(int index, bool addFromCurrentScene, bool resetScene) {
	lastSceneIndex = currentSceneIndex;

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
	currentScene->UpdateSwitch();

	if (resetScene)
		currentScene->InitScene();
}

/*
static Game *instance() {if (!_inst) _inst = new Game(); return _inst;}
static S& instance() { static S inst; return inst; }
   38
37 40 39
*/