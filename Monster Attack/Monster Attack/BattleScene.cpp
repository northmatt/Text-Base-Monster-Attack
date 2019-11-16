#include "BattleScene.h"
#include "TestEntity.h"

void BattleScene::InitScene() {
	cout << "battleInit\n";
	entities.push_back(new TestEnt("    \n    ", "Player", 3, 3));
}

void BattleScene::UpdateScene() {
	timeSinceStart += Time::deltaTime;
	string outputChar = "Time: " + to_string(static_cast<int>(timeSinceStart));
	Game::shared_instance().buffer.WriteBuffer(outputChar, 0, 0, 6);

	for (Entity* currentEnt : entities)
		currentEnt->Update();

	//switch between scenes
	if (Input::GetKeyDown('A'))
		Game::shared_instance().SwitchToScene(-1, true);
	else if (Input::GetKeyDown('D'))
		Game::shared_instance().SwitchToScene(1, true);
}