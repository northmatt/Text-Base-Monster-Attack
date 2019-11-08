#include "Game.h"

void Game::InitGame() {
	cout << "init\n";
	loadedScenes.push_back(new BattleScene());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	currentScene->UpdateScene();

	return false;
}
