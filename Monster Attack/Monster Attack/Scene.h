#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include "Input.h"
#include "Time.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Scene {
public:
	Scene() { InitScene(); };
	Scene(string name);
	~Scene() {}
	//want virtual so that classes that inherinent the Scene class will run the inherinented class instead of the original Scene class (this one)
	virtual void InitScene();
	virtual void UpdateScene();
private:
	string name;
};