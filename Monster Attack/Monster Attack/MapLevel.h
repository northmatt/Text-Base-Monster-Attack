#pragma once

#include <fstream>
#include <sstream>
#include "Game.h"
#include "Monsters.h"
#include "BattlePlayer.h"

using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::getline;

class MapLevel : public Scene {
public:
	MapLevel() { }

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();

	void Load(string fileName);
};