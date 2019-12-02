#pragma once

#include <fstream>
#include "Game.h"

using std::ofstream;
using std::ifstream;
using std::getline;

class LoseScreen : public Scene {
public:
	LoseScreen() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();
	void LoadIntoString(string fileName, string &stringToEdit);
private:
	string title{ "" };
	int selection{ 0 };
	double centerOfScreen{ 0 };
};