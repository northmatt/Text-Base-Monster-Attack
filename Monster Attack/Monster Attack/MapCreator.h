#pragma once

#include "Scene.h"
#include "Game.h"

class MapCreator : public Scene {
public:
	static MapCreator& shared_instance() { static MapCreator mapEdit; return mapEdit; }

	MapCreator() { InitScene(); };
	~MapCreator() {}

	void InitScene();
	void UpdateScene();
private:
	unsigned int mapWidth{ 0 }, mapHeight{ 0 }, mapSize{ 0 };
	string mapBorder;
	char* writeScreen;
	int* colorScreen;
	vector<Entity*> entities;
};