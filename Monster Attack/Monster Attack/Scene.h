#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include "Input.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Scene {
public:
	Scene() { InitScene(); };
	Scene(string name);
	~Scene() {}

	virtual void InitScene();
	virtual void UpdateScene();
private:
	string name;
};