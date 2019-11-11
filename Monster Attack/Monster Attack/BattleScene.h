#pragma once

#include "Scene.h"

class BattleScene : public Scene {
public:
	BattleScene() { InitScene(); };
	~BattleScene() { }

	void InitScene();
	void UpdateScene();
private:
	double timeSinceStart{ 0 };
};