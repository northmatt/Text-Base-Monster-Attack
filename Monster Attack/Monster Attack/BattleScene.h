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
		Monster mon[6];
		Monster currentMon;
		int currentMonSlot = 1;
	};

	void drawCurrentHealth(Party p1, Party p2);
	void showPlayerMoves(Move m1);
	int damageCalculator(bool player1Turn, Monster attacker, Monster defender, Move attack);
	int playerTurn(bool player1Turn, Monster p1, Monster p2);

	Party party1, party2;
};