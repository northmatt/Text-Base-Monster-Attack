#pragma once

#include <algorithm>
#include <random>
#include "Game.h"
#include "Monsters.h"

class BattleScene : public Scene {
public:
	BattleScene() { }

	void InitScene();
	void UpdateScene();
private:
	void drawCurrentHealth(Party p1, Party p2);
	void showPlayerMoves(vector<Move> ms);
	void playerTurn(Party &p1, Party &p2);
	void damageCalculator(Monster *attacker, Monster *defender, Move *attack, int checkType = 0);

	Party party1, party2;
	bool p1Turn{ false };
	string damageStr;
	double damageTime;
};