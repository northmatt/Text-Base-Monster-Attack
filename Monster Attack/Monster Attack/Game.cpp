#include "Game.h"
#include "Titlescreen.h"
#include "Pausescreen.h"
#include "MapCreator.h"
#include "BattleScene.h"
#include "MapLevel.h"
#include "BattleSceneAI.h"


void Game::InitGame() {
	srand(time(0));

	//loads the scenes into memory
	loadedScenes.push_back(new Titlescreen());
	loadedScenes.push_back(new Pausescreen());
	loadedScenes.push_back(new MapCreator());
	loadedScenes.push_back(new BattleScene());
	loadedScenes.push_back(new MapLevel());
	loadedScenes.push_back(new BattleSceneAI());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	//cap FPS
	Time::FpsCap();

	Input::updateInps();

	isRunning = !Input::GetKeyDown(VK_F4);

	currentScene->UpdateScene();

	buffer.DisplayBuffer();

	if (switchingToScene > 0)
		internalSwitchScene();

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

	if (resetScene)
		switchingToScene = 2;
	else
		switchingToScene = 1;
}

void Game::internalSwitchScene() {
	currentScene->BeforeUpdateSwitch();

	currentScene = loadedScenes[currentSceneIndex];
	currentScene->UpdateSwitch();

	if (switchingToScene == 2)
		currentScene->InitScene();

	switchingToScene = 0;
}

/*
static Game *instance() {if (!_inst) _inst = new Game(); return _inst;}
static S& instance() { static S inst; return inst; }
   38
37 40 39
*/