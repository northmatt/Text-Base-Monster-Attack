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

	if (Input::GetKeyDown(VK_NUMPAD4))
		colorValInd = !colorValInd;

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

	/*for (size_t y = 0; y < 2; y++) {
		for (size_t x = 0; x < 4; x++) {
			Game::shared_instance().buffer.WriteBuffer(to_string(colorValues[y][x]), 0, x + 4 * y);
		}
	}*/

	Game::shared_instance().buffer.SetCamPos({ static_cast<int>(round(pos.x)), static_cast<int>(round(pos.y)) });
	Game::shared_instance().buffer.WriteBuffer(image, round(pos.x), pos.y, color);
}
