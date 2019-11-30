#pragma once

#include <fstream>
#include "Scene.h"
#include "Game.h"

using std::ofstream;
using std::ifstream;
using std::getline;

class Titlescreen : public Scene {
public:
	Titlescreen() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();
	void LoadIntoString(string fileName, string &stringToEdit);
private:
	string title{ "" };
	int selection{ 0 };
	double centerOfScreen{ 0 };
};