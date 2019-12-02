#pragma once

#include <string>
#include "Vectors.h"

using std::string;

class Entity {
public:
	Entity() {}
	Entity(string theName) { name = theName; }

	virtual void Update(size_t _index) { curIndex = _index; }

	string name{ "" };
	Vec2 pos;
	string image{ "" };
	int color{ 0 };
	int curIndex{ 0 };
};