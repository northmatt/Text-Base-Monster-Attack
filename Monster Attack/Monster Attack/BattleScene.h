#pragma once

#include "Scene.h"

class BattleScene : public Scene {
public:
	BattleScene() { init(); };
	~BattleScene() { }

	void init();
	void UpdateScene();
private:
	int test2;
};