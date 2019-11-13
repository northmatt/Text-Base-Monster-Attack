#include "BattleScene.h"

void BattleScene::InitScene() {
	cout << "battleInit\n";
}

void BattleScene::UpdateScene() {
	timeSinceStart += Time::deltaTime;
	cout << "Time: " << static_cast<int>(timeSinceStart) << "\n";
	
	string outputChar{ "" };

	if (Input::GetKeyDown(37))
		outputChar += "left ";
	if (Input::GetKeyDown(39))
		outputChar += "right ";

	if (Input::GetKeyDown(38))
		outputChar += "up ";
	if (Input::GetKeyDown(40))
		outputChar += "down ";

	outputChar += "BattleScene Update";
	cout << outputChar;

	//switch between scenes
	if (Input::GetKeyDown('A'))
		Game::shared_instance().SwitchToScene(0);
	else if (Input::GetKeyDown('D'))
		Game::shared_instance().SwitchToScene(1);
}