#pragma once

#include <fstream>
#include "Game.h"

using std::ofstream;
using std::ifstream;
using std::getline;

class IntroScreen : public Scene {
public:
	IntroScreen() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void UpdateSwitch();
	void LoadIntoString(string fileName, string &stringToEdit);
private:
	string title{ "" };
	string bodyText{ "" };
	int selection{ 0 };
	double centerOfScreen{ 0 };
};