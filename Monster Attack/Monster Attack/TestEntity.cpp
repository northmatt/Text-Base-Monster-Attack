#include "TestEntity.h"

TestEnt::TestEnt(string inImage, string inName, double inPosX, double inPosY) {
	pos = Vec2{ inPosX, inPosY };
	image = inImage;
	name = inName;
}

void TestEnt::Update() {
	if (Input::GetKeyDown(37))
		vel.x -= 1;
	if (Input::GetKeyDown(39))
		vel.x += 1;

	if (Input::GetKeyDown(38))
		vel.y -= 1;
	if (Input::GetKeyDown(40))
		vel.y += 1;

	vel = vel.Normalize();
	vel.x *= 2;

	vel = vel * Time::deltaTime;
	pos = pos + vel * speed;

	vel.Zero();

	Game::shared_instance().buffer.WriteBuffer(image, static_cast<int>(pos.x) / 2 * 2, static_cast<int>(pos.y), 20);
}
