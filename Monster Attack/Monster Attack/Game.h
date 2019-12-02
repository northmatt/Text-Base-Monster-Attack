#pragma once

#include "Scene.h"
#include "Display.h"
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

using std::vector;

class Game {
public:
	static Game& shared_instance() { static Game game; return game; }

	void InitGame();
	bool UpdateGame();
	void SwitchToScene(int index, bool addFromCurrentScene = false, bool resetScene = false);
	Scene* GetCurrentScene() { return currentScene; }
	int GetCurrentSceneIndex() { return currentSceneIndex; }
	int GetLastSceneIndex() { return lastSceneIndex; }
	Entity* GetMainPlayer() { return MainPlayer; }
	Entity* GetMainEnemy() { return Enemy; }
	void SetMainPlayer(Entity* _MP) { MainPlayer = _MP; }
	void SetMainEnemy(Entity* _MP) { Enemy = _MP; }
	void PlayMusic(string songName, bool stopOld = true);
	DoubleBuffer buffer;
	bool isRunning{ true };
private:
	void internalSwitchScene();
	Scene* currentScene{ nullptr };
	int currentSceneIndex{ 0 };
	int lastSceneIndex{ 0 };
	int switchingToScene{ 0 };
	vector<Scene*> loadedScenes;
	Entity* MainPlayer;
	Entity* Enemy;
};