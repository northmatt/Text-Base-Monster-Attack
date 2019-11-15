#pragma once

#include "entity.h"
#include "Game.h"

using std::round;

class TestEnt : public Entity {
public:
	TestEnt(string inImage, string inName, double inPosX, double inPosY);
	~TestEnt() {}
	void Update();
private:
	Vec2 vel;
	double speed{ 8 };
};