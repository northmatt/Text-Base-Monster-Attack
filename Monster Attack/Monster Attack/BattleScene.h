#pragma once

#include "Scene.h"

class BattleScene : public Scene {
public:
	BattleScene() { InitScene(); };
	~BattleScene() { }

	void InitScene();
	void UpdateScene();
private:
	int test2;
	Input inp;
};