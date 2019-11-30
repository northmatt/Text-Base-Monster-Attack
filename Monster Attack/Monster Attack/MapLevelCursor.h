#pragma once

#include "entity.h"
#include "Game.h"

using std::round;

class MapLevelCursor : public Entity {
public:
	MapLevelCursor(string inImage, string inName, double inPosX, double inPosY);

	void Update();
private:
	Vec2 vel;
	Vec2 maxPos;
	double speed{ 8 };
};