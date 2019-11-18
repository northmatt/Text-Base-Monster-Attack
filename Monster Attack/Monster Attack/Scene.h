#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include "Input.h"
#include "Time.h"
#include "entity.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

class Scene {
public:
	Scene() { };
	Scene(string name);

	//want virtual so that classes that inherinent the Scene class will run the inherinented class instead of the original Scene class (this one)
	void InitScene();
	virtual void UpdateScene();
	virtual void UpdateSwitch();
private:
	string name;
};