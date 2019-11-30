#pragma once

#include <fstream>
#include <sstream>
#include "Scene.h"
#include "Game.h"

using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::getline;

class MapLevel : public Scene {
public:
	MapLevel() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();

	void Load(string fileName);
};