#pragma once

#include "Scene.h"
#include "Game.h"

class MapCreator : public Scene {
public:
	static MapCreator& shared_instance() { static MapCreator mapEdit; return mapEdit; }

	MapCreator() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();
};