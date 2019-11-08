#include "Game.h"

void Game::InitGame() {
	cout << "init\n";
	loadedScenes.push_back(new BattleScene());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	cout << "update\n";

	currentScene->UpdateScene();

	return false;
}
