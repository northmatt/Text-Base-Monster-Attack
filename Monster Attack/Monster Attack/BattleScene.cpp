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
	
	char* outChar = &outputChar[0];
	Game::shared_instance().buffer.WriteBuffer(0, 1, outChar, 20);

	//switch between scenes
	if (Input::GetKeyDown('A'))
		Game::shared_instance().SwitchToScene(0);
	else if (Input::GetKeyDown('D'))
		Game::shared_instance().SwitchToScene(1);
}