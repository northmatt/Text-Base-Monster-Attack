#pragma once

#include <vector>
#include <cstdio>
#include <chrono>
#include <thread>
#include "Input.h"
#include "Scene.h"
#include "BattleScene.h"

using std::vector;
using std::milli;
using std::chrono::system_clock;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

class Game {
public:
	void InitGame();
	bool UpdateGame();
	void FpsCap();
private:
	HANDLE hConsole;
	double timeWait{ 16.667 };
	system_clock::time_point a = system_clock::now();
	system_clock::time_point b = system_clock::now();
	Scene* currentScene;
	vector<Scene*> loadedScenes;
	Input inp;
};