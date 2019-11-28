#pragma once

#include "Scene.h"
#include "Game.h"
#include "Monster.h"

class BattleScene : public Scene {
public:
	BattleScene() { InitScene(); };

	void InitScene();
	void UpdateScene();
private:
	struct Party {
		string name;
		Monster mon[6];
		Monster currentMon;
		int currentMonSlot = 1;
	};

	void drawCurrentHealth(Party p1, Party p2);
	void showPlayerMoves(vector<Move> ms);
	void playerTurn(Party &p1, Party &p2);
	void damageCalculator(Monster &attacker, Monster &defender, Move attack, bool checkPassive = true);

	Party party1, party2;
	bool p1Turn{ false };
	string damageStr;
	float damageTime;
};