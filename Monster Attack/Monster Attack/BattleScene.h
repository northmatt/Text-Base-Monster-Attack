#pragma once

#include "Scene.h"

class BattleScene : public Scene {
public:
	BattleScene() { init(); };
	~BattleScene() { }

	void init();
private:
	int test2;
};