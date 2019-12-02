#pragma once

#include <algorithm>
#include "Input.h"
#include "Time.h"
#include "entity.h"

using std::cout;
using std::cin;
using std::sort;
using std::endl;
using std::string;
using std::to_string;

class Scene {
public:
	Scene() { };
	Scene(string name);

	//want virtual so that classes that inherinent the Scene class will run the inherinented class instead of the original Scene class (this one)
	virtual void InitScene();
	virtual void UpdateScene();
	virtual void UpdateSwitch();
	virtual void BeforeUpdateSwitch() {}
	void removeEntity(size_t i) { entsToRemove.push_back(i); }
	void removeEntities() {
		sort(entities.begin(), entities.end());

		for (size_t i = 0; i < entsToRemove.size(); i++) {
			entities.erase(entities.begin() + entsToRemove[i] - i);
		}

		entsToRemove.clear();
	}
	void addEntity(Entity* _ent) { entsToAdd.push_back(_ent); }
	void addEntities() {
		for (Entity* curEnt : entsToAdd)
			entities.insert(entities.end(), &*curEnt);

		entsToAdd.clear();
	}

	vector<int> map{ 0, 0 };
	unsigned int mapSize{ 0 };
	string mapBorder{ "" };
	vector<char> writeScreen;
	vector<int> colorScreen;
	vector<Entity*> entities;

private:
	string name;
	vector<size_t> entsToRemove;
	vector<Entity*> entsToAdd;
};