#pragma once

#include <vector>
#include "Input.h"
#include "Scene.h"
#include "Time.h"

using std::vector;

class Game {
public:
	static Game& shared_instance() { static Game game; return game; }

	void InitGame();
	bool UpdateGame();
	void SetCurPos(SHORT x, SHORT y);
	void SwitchToScene(int index, bool addFromCurrentScene = false);
private:
	HANDLE hConsole;
	Scene* currentScene{ nullptr };
	int currentSceneIndex{ 0 };
	vector<Scene*> loadedScenes;
};