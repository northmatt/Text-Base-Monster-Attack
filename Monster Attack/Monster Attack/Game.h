#pragma once

#include <vector>
#include "Input.h"
#include "Scene.h"
#include "Time.h"
#include "Display.h"

using std::vector;

class Game {
public:
	static Game& shared_instance() { static Game game; return game; }

	void InitGame();
	bool UpdateGame();
	void SwitchToScene(int index, bool addFromCurrentScene = false);
	Scene* GetCurrentScene() { return currentScene; }
	DoubleBuffer buffer;
private:
	Scene* currentScene{ nullptr };
	int currentSceneIndex{ 0 };
	vector<Scene*> loadedScenes;
	Entity* MainPlayer{ nullptr };
};