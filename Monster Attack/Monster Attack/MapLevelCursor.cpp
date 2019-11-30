#include "MapLevelCursor.h"

#include "TestEntity.h"

MapLevelCursor::MapLevelCursor(string inImage, string inName, double inPosX, double inPosY) {
	pos = Vec2{ 1, 1 };
	image = inImage;
	name = inName;
	maxPos = Vec2{ inPosX, inPosY };
}

void MapLevelCursor::Update() {
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

	//string outputChar = "Pos: " + to_string(pos.x) + ", " + to_string(pos.y);
	//Game::shared_instance().buffer.WriteBuffer(outputChar, 0, 1, 5);

	Game::shared_instance().buffer.SetCamPos({ static_cast<int>(round(pos.x)), static_cast<int>(round(pos.y)) });
	Game::shared_instance().buffer.WriteBuffer(image, round(pos.x), pos.y, 0);
}
