#pragma once

#include "Scene.h"
#include "Game.h"

class BattleScene : public Scene {
public:
	BattleScene() { InitScene(); };
	~BattleScene() { }

	void InitScene();
	void UpdateScene();
private:
	double timeSinceStart{ 0 };
	vector<Entity*> entities;
};