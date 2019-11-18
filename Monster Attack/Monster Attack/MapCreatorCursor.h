#pragma once

#include "Scene.h"
#include "Game.h"

using std::round;

class MapCreatorCursor : public Entity {
public:
	MapCreatorCursor(string inImage, string inName, double inPosX, double inPosY, int col);

	void Update();
private:
	Vec2 vel;
	double speed{ 8 };
	Vec2 maxPos;

	vector<vector<bool>> colorValues;
	bool colorValInd{ false };
	bool isDrawing{ false };
};