#pragma once

#include "Game.h"
#include "BattlePlayer.h"

class BattleSceneAI : public Scene {
public:
	BattleSceneAI() { InitScene(); };

	void InitScene();
	void UpdateScene();
	void BeforeUpdateSwitch();
	void UpdateSwitch();

private:
	void drawCurrentHealth(Party p1, Party p2);
	void showPlayerMoves(vector<Move> ms);
	void playerTurn(Party &p1, Party &p2);
	void damageCalculator(Monster *attacker, Monster *defender, Move *attack, int checkType = 0);

	Party party1, party2;
	bool p1Turn{ true };
	string damageStr;
	double damageTime;
};