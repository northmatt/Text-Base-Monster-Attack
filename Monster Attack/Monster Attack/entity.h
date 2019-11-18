#pragma once

#include <string>
#include "Vectors.h"

using std::string;

class Entity {
public:
	Entity() {}
	Entity(string theName) { name = theName; }

	virtual void Update() {}

	string name;
	Vec2 pos;
	string image{ "" };
	int color{ 0 };
};