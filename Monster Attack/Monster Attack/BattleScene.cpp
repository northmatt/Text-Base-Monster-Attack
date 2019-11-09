#include "BattleScene.h"

void BattleScene::InitScene() {
	cout << "battleInit\n";
}

void BattleScene::UpdateScene() {
	if (inp.GetKeyDown(37))
		cout << "left ";
	if (inp.GetKeyDown(39))
		cout << "right ";

	if (inp.GetKeyDown(38))
		cout << "up ";
	if (inp.GetKeyDown(40))
		cout << "down ";

	cout << "battleUpdate\n";
}