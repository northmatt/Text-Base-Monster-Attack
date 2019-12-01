#pragma once

#include <fstream>
#include <sstream>
#include "Scene.h"
#include "Game.h"

using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::getline;

class MapCreator : public Scene {
public:
	MapCreator() { };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();

	void Save(string fileName, vector<int> sizeMap, vector<char> writeMap, vector<int> colorMap);
	void Load(string fileName);
};