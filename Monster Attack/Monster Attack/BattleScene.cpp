#include "BattleScene.h"

void BattleScene::InitScene() {
	cout << "battleInit\n";
}

void BattleScene::UpdateScene() {
	string outputChar{ "" };

	timeSinceStart += Time::deltaTime;
	outputChar += "Time: " + to_string(static_cast<int>(timeSinceStart)) + "\n";

	if (Input::GetKeyDown(37))
		outputChar += "left ";
	if (Input::GetKeyDown(39))
		outputChar += "right ";

	if (Input::GetKeyDown(38))
		outputChar += "up ";
	if (Input::GetKeyDown(40))
		outputChar += "down ";

	outputChar += "BattleScene Update";
	Game::shared_instance().buffer.WriteBuffer(outputChar, 0, 1, 20);
	Game::shared_instance().buffer.WriteBuffer("This is a simple Test\nTessTTT", 4, 2, 25);

	//switch between scenes
	if (Input::GetKeyDown('A'))
		Game::shared_instance().SwitchToScene(0);
	else if (Input::GetKeyDown('D'))
		Game::shared_instance().SwitchToScene(1);
}