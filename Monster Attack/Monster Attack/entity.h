#pragma once

#include <string>
#include "Vectors.h"

using std::string;

class Entity {
public:
	Entity() {};
	Entity(string theName) {name = theName};
	~Entity() {}

	void Update();
private:
	string name;
	Vec2 pos{ 0, 0 };
	string image{ "" };
};