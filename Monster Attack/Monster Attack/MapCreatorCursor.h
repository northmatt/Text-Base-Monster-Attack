#pragma once

#include <stack>
#include "Scene.h"
#include "Game.h"

using std::round;
using std::stack;

class MapCreatorCursor : public Entity {
public:
	MapCreatorCursor(string inImage, string inName, double inPosX, double inPosY, int col);

	void Update();
	void FillLoop(vector<int> pos, int direction, char oldChar, int oldColor);
private:
	Vec2 vel;
	double speed{ 8 };
	Vec2 maxPos;

	vector<vector<bool>> colorValues;
	vector<int> spawnPoint{ 1, 1 };
	bool colorValInd{ false };
	bool isDrawing{ false };
};