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

		color = 1;

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
		size_t currSize{ 1 };
		size_t preSize{ 0 };
		vector<vector<int>> posList;
		vector<vector<int>> movePoints{ {0, 1}, {2, 0}, {0, -1}, {-2, 0} };
		posList.push_back({ static_cast<int>(round(pos.x - 1) * 2), static_cast<int>(round(pos.y - 1)), 0 });
		char currentChar = Game::shared_instance().GetCurrentScene()->writeScreen[posList[0][0] + posList[0][1] * maxPos.x * 2];
		int currentColor = Game::shared_instance().GetCurrentScene()->colorScreen[posList[0][0] + posList[0][1] * maxPos.x * 2];
		/*
		3012031
		1000101
		1200110
		0011101

		ran starting on a "0"

		0100000
		0111010
		0011001
		1100010
		*/
		while (currSize != preSize) {
			preSize = currSize;
			currSize = posList.size();
			for (size_t i = 0; i < posList.size(); i++) {
				if (posList[i][2] == 1)
					continue;

				for (vector<int> moveVec : movePoints) {
					bool exists{ false };
					vector<int> toAddVec{ posList[i][0] + moveVec[0], posList[i][1] + moveVec[1], 0 };

					//add code to detect if point is on different curr Char/Color or off map
					if (toAddVec[0] < 0 || toAddVec[0] >= maxPos.x * 2 || toAddVec[1] < 0 || toAddVec[1] >= maxPos.y)
						continue;

					if (Game::shared_instance().GetCurrentScene()->writeScreen[toAddVec[0] + toAddVec[1] * maxPos.x * 2] != currentChar || Game::shared_instance().GetCurrentScene()->colorScreen[toAddVec[0] + toAddVec[1] * maxPos.x * 2] != currentColor)
						continue;

					for (vector<int> checkCol : posList)
						if (toAddVec[0] == checkCol[0] && toAddVec[1] == checkCol[1]) {
							exists = true;
							break;
						}

					if (exists)
						continue;

					posList[i][2] = 1;
					posList.push_back(toAddVec);
				}
			}
		}

		for (vector<int> currVec : posList) {
			for (size_t index = 0; index < 2; index++) {
				Game::shared_instance().GetCurrentScene()->writeScreen[currVec[0] + index + currVec[1] * maxPos.x * 2] = currentChar;
				Game::shared_instance().GetCurrentScene()->colorScreen[currVec[0] + index + currVec[1] * maxPos.x * 2] = color;
			}
		}
	}

	/*for (size_t y = 0; y < 2; y++) {
		for (size_t x = 0; x < 4; x++) {
			Game::shared_instance().buffer.WriteBuffer(to_string(colorValues[y][x]), 0, x + 4 * y);
		}
	}*/

	Game::shared_instance().buffer.SetCamPos({ static_cast<int>(round(pos.x)), static_cast<int>(round(pos.y)) });
	Game::shared_instance().buffer.WriteBuffer(image, round(pos.x), pos.y, color);
}