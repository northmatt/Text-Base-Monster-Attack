#pragma once

#include "entity.h"
#include "Game.h"

using std::round;

class MapCreatorCursor : public Entity {
public:
	MapCreatorCursor(string inImage, string inName, double inPosX, double inPosY);
	~MapCreatorCursor() {}
	void Update();
private:
	Vec2 vel;
	double speed{ 8 };
	Vec2 maxPos;
};