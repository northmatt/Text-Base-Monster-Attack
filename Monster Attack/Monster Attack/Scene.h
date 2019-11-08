#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Scene {
public:
	Scene() {};
	Scene(string name);
	~Scene() {}

	virtual void UpdateScene();
private:
	string name;
};