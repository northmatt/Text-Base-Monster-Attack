#pragma once

#include <fstream>
#include "Game.h"
#include "BattlePlayer.h"

using std::ofstream;
using std::ifstream;
using std::getline;

class MultiplayerWin : public Scene {
public:
	MultiplayerWin() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();
	void LoadIntoString(string fileName, string &stringToEdit);
private:
	int centerText{ 0 };
	string winner{ "" };
	string win1{ "" };
	string win2{ "" };
	int selection{ 0 };
	double centerOfScreen{ 0 };
};