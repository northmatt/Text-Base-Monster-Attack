#include "Game.h"
#include "BattleScene.h"
#include "MapCreator.h"

void Game::InitGame() {
	cout << "Game Init (press 'q' to quit) (use arrow keys) (use 'a' or 'd')\n";

	//loadedScenes.push_back(new BattleScene());
	//loadedScenes.push_back(new BattleScene());
	loadedScenes.push_back(new MapCreator());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	//cap FPS
	Time::FpsCap();

	Input::updateInps();

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
	currentScene->UpdateSwitch();
}

/*
static Game *instance() {if (!_inst) _inst = new Game(); return _inst;}
static S& instance() { static S inst; return inst; }
   38
37 40 39
*/