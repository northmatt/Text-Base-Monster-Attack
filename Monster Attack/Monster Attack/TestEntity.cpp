#include "TestEntity.h"

TestEnt::TestEnt(string inImage, string inName, double inPosX, double inPosY) {
	pos = Vec2{ inPosX, inPosY };
	image = inImage;
	name = inName;
}

void TestEnt::Update() {
	if (Input::GetKey(37))
		vel.x -= 1;
	if (Input::GetKey(39))
		vel.x += 1;

	if (Input::GetKey(38))
		vel.y -= 1;
	if (Input::GetKey(40))
		vel.y += 1;

	vel = vel.Normalize() * Time::deltaTime;
	pos = pos + vel * speed;

	vel.Zero();

	string outputChar = "Pos: " + to_string(pos.x) + ", " + to_string(pos.y);
	Game::shared_instance().buffer.WriteBuffer(outputChar, 0, 1, 5);

	Game::shared_instance().buffer.WriteBuffer(image, round(pos.x), pos.y, 20);
}
