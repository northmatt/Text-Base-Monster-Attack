#include "MapCreatorCursor.h"

MapCreatorCursor::MapCreatorCursor(string inImage, string inName, double inPosX, double inPosY, int col) {
	pos = Vec2{ 1, 1 };
	image = inImage;
	name = inName;
	maxPos = Vec2{ inPosX, inPosY };
	color = col;

	colorValues.assign(2, { false, false, false, false });
}

void MapCreatorCursor::Update() {
	//movement
	{
		if (Input::GetKey(37))
			vel.x -= 1;
		if (Input::GetKey(39))
			vel.x += 1;

		if (Input::GetKey(38))
			vel.y -= 1;
		if (Input::GetKey(40))
			vel.y += 1;

		vel = vel.Normalize() * Time::deltaTime;

		if (Input::GetKey(VK_CONTROL))
			vel = vel * 1.5;

		pos = pos + vel * speed;

		vel.Zero();

		if (pos.x < 1)
			pos.x = 1;
		else if (pos.x > maxPos.x)
			pos.x = maxPos.x;

		if (pos.y < 1)
			pos.y = 1;
		else if (pos.y > maxPos.y)
			pos.y = maxPos.y;
	}

	//basic drawing
	{
		if (Input::GetKeyDown(VK_NUMPAD4))
			colorValInd = !colorValInd;

		if (Input::GetKeyDown(VK_SPACE))
			isDrawing = !isDrawing;

		if (Input::GetKeyDown(VK_NUMPAD7))
			colorValues[colorValInd][0] = !colorValues[colorValInd][0];
		else if (Input::GetKeyDown(VK_NUMPAD8))
			colorValues[colorValInd][1] = !colorValues[colorValInd][1];
		else if (Input::GetKeyDown(VK_NUMPAD9))
			colorValues[colorValInd][2] = !colorValues[colorValInd][2];
		else if (Input::GetKeyDown(VK_NUMPAD5))
			colorValues[colorValInd][3] = !colorValues[colorValInd][3];

		color = 0;

		if (colorValues[0][0])
			color = color | FOREGROUND_RED;
		if (colorValues[0][1])
			color = color | FOREGROUND_GREEN;
		if (colorValues[0][2])
			color = color | FOREGROUND_BLUE;
		if (colorValues[0][3])
			color = color | FOREGROUND_INTENSITY;

		if (colorValues[1][0])
			color = color | BACKGROUND_RED;
		if (colorValues[1][1])
			color = color | BACKGROUND_GREEN;
		if (colorValues[1][2])
			color = color | BACKGROUND_BLUE;
		if (colorValues[1][3])
			color = color | BACKGROUND_INTENSITY;

		if (isDrawing)
			for (size_t i = 0; i < 2; i++) {
				Game::shared_instance().GetCurrentScene()->writeScreen[round(pos.x - 1) * 2 + i + round(pos.y - 1) * maxPos.x * 2] = ' ';
				Game::shared_instance().GetCurrentScene()->colorScreen[round(pos.x - 1) * 2 + i + round(pos.y - 1) * maxPos.x * 2] = color;
			}
	}

	//fill function
	if (Input::GetKeyDown('P')) {
		vector<int> currentPos{ static_cast<int>(round(pos.x - 1) * 2), static_cast<int>(round(pos.y - 1)), 0 };
		char currentChar = Game::shared_instance().GetCurrentScene()->writeScreen[currentPos[0] + currentPos[1] * maxPos.x * 2];
		int currentColor = Game::shared_instance().GetCurrentScene()->colorScreen[currentPos[0] + currentPos[1] * maxPos.x * 2];

		if (currentColor != color)
			FillLoop(currentPos, -1, currentChar, currentColor);
	}

	string guiOverlay = "F(" + to_string(colorValues[0][0] * (1 + colorValues[0][3])) + ", " + to_string(colorValues[0][1] * (1 + colorValues[0][3])) + ", " + to_string(colorValues[0][2] * (1 + colorValues[0][3])) + ")";
	guiOverlay += "  B(" + to_string(colorValues[1][0] * (1 + colorValues[1][3])) + ", " + to_string(colorValues[1][1] * (1 + colorValues[1][3])) + ", " + to_string(colorValues[1][2] * (1 + colorValues[1][3])) + ")";
	guiOverlay += " Color: " + to_string(color);

	Game::shared_instance().buffer.WriteBuffer(guiOverlay, 0, 0);

	Game::shared_instance().buffer.SetCamPos({ static_cast<int>(round(pos.x)), static_cast<int>(round(pos.y)) });
	Game::shared_instance().buffer.WriteBuffer(image, round(pos.x), pos.y, color);
}

void MapCreatorCursor::FillLoop(vector<int> pos, int direction, char oldChar, int oldColor) {
	//needed to do an iterative function for this recursive function as stack overflow error would happen
	vector<vector<int>> movePoints{ {0, 1}, {2, 0}, {0, -1}, {-2, 0} };

	struct SnapShotStruct {
		vector<int> pos;
		int direction{ 0 };
		char oldChar{ 0 };
		int oldColor{ 0 };
	};

	stack<SnapShotStruct> snapshotStack;
	// (Fourth rule)
	SnapShotStruct currentSnapshot;
	currentSnapshot.pos = pos;
	currentSnapshot.direction = direction;
	currentSnapshot.oldChar = oldChar;
	currentSnapshot.oldChar = oldColor;
	snapshotStack.push(currentSnapshot);

	while (!snapshotStack.empty()) {
		currentSnapshot = snapshotStack.top();
		snapshotStack.pop();

		for (size_t i = 0; i < movePoints.size(); i++)
			if (i != (currentSnapshot.direction >= 2 ? currentSnapshot.direction - 2 : currentSnapshot.direction + 2)) {
				vector<int> newVec{ currentSnapshot.pos[0] + movePoints[i][0], currentSnapshot.pos[1] + movePoints[i][1] };

				//add code to detect if point is on different curr Char/Color or off map
				if (newVec[0] < 0 || newVec[0] >= maxPos.x * 2 || newVec[1] < 0 || newVec[1] >= maxPos.y)
					continue;

				if (Game::shared_instance().GetCurrentScene()->writeScreen[newVec[0] + newVec[1] * maxPos.x * 2] != oldChar || Game::shared_instance().GetCurrentScene()->colorScreen[newVec[0] + newVec[1] * maxPos.x * 2] != oldColor)
					continue;

				for (size_t index = 0; index < 2; index++) {
					Game::shared_instance().GetCurrentScene()->writeScreen[newVec[0] + index + newVec[1] * maxPos.x * 2] = oldChar;
					Game::shared_instance().GetCurrentScene()->colorScreen[newVec[0] + index + newVec[1] * maxPos.x * 2] = color;
				}

				snapshotStack.push(currentSnapshot);

				SnapShotStruct newSnapshot;
				newSnapshot.pos = newVec;
				newSnapshot.direction = i;
				newSnapshot.oldChar = oldChar;
				newSnapshot.oldChar = oldColor;

				snapshotStack.push(newSnapshot);
			}
	}
}