#pragma once

#include <vector>
#include "Input.h"
#include "Scene.h"
#include "Time.h"

using std::vector;

class Game {
public:
	void InitGame();
	bool UpdateGame();
	void SetCurPos(SHORT x, SHORT y);
private:
	HANDLE hConsole;
	Scene* currentScene;
	vector<Scene*> loadedScenes;
};