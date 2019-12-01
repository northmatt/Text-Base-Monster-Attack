#pragma once

#include "entity.h"
#include "Game.h"
#include "Monsters.h"

using std::round;

class BattlePlayer : public Entity {
public:
	BattlePlayer(string name, int curMonIndex, Monster _m1, Monster _m2 = Monster{}, Monster _m3 = Monster{}, Monster _m4 = Monster{}, Monster _m5 = Monster{}, Monster _m6 = Monster{});
	BattlePlayer() {}

	Monster mon[6]{ Monster{} };
	int currentMonSlot{ 0 };
};