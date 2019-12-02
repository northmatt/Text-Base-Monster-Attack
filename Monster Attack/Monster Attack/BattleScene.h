#pragma once

#include <algorithm>
#include <random>
#include "Game.h"
#include "BattlePlayer.h"

class BattleScene : public Scene {
public:
	BattleScene() { }

	void InitScene();
	void UpdateScene();
	void UpdateSwitch() { Game::shared_instance().PlayMusic("15-birth-of-a-god"); }
private:
	void drawCurrentHealth(Party p1, Party p2);
	void showPlayerMoves(vector<Move> ms);
	void playerTurn(Party &p1, Party &p2);
	void damageCalculator(Monster *attacker, Monster *defender, Move *attack, int checkType = 0);

	Party party1, party2;
	bool p1Turn{ false };
	int selection{ 0 };
	string damageStr;
	double damageTime;
};