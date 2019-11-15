#include "BattleScene.h"
#include "TestEntity.h"

void BattleScene::InitScene() {
	cout << "battleInit\n";
	entities.push_back(new TestEnt("    \n    ", "Player", 3, 3));
}

void BattleScene::UpdateScene() {
	timeSinceStart += Time::deltaTime;
	string outputChar = "Time: " + to_string(static_cast<int>(timeSinceStart)) + "\n";
	Game::shared_instance().buffer.WriteBuffer(outputChar, 0, 0, 6);

	for (Entity* currentEnt : entities)
		currentEnt->Update();

	//switch between scenes
	if (Input::GetKeyDown('A'))
		Game::shared_instance().SwitchToScene(0);
	else if (Input::GetKeyDown('D'))
		Game::shared_instance().SwitchToScene(1);
}

/*if (Input::GetKeyDown(37))
		outputChar += "left ";
	if (Input::GetKeyDown(39))
		outputChar += "right ";

	if (Input::GetKeyDown(38))
		outputChar += "up ";
	if (Input::GetKeyDown(40))
		outputChar += "down ";

	outputChar += "BattleScene Update";
	Game::shared_instance().buffer.WriteBuffer(outputChar, 0, 1, 20);
	Game::shared_instance().buffer.WriteBuffer("This is a simple Test\nTessTTT", 4, 2, 25);*/