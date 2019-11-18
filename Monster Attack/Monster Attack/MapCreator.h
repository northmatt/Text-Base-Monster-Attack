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
private:
	vector<int> map;
	unsigned int mapSize{ 0 };
	string mapBorder{ "" };
	vector<char> writeScreen;
	vector<int> colorScreen;
	vector<Entity*> entities;
};