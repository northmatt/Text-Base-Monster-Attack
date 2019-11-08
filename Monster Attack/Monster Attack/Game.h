#pragma once

#include <vector>
#include "Scene.h"
#include "BattleScene.h"

using std::vector;

class Game {
public:
	void InitGame();
	bool UpdateGame();
private:
	Scene* currentScene;
	vector<Scene*> loadedScenes;
};