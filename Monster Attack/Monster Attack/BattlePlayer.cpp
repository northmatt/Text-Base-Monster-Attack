#include "BattlePlayer.h"

//BattlePlayer* player = (BattlePlayer*)entities[0]
BattlePlayer::BattlePlayer(string _name, int CurMonIndex, Monster _m1, Monster _m2, Monster _m3, Monster _m4, Monster _m5, Monster _m6) {
	name = _name;
	currentMonSlot = CurMonIndex;
	mon[0] = _m1;
	mon[1] = _m2;
	mon[2] = _m3;
	mon[3] = _m4;
	mon[4] = _m5;
	mon[5] = _m6;

	FindNumMons();
}

void BattlePlayer::healMons() {
	healed = true;
	currentMonSlot = 0;
	for (size_t i = 0; i < 6; i++) {
		if (mon[i].getName() == "NULL")
			return;

		mon[i].resetAll();
	}
}

void BattlePlayer::FindNumMons() {
	for (size_t i = 0; i < 6; i++) {
		if (mon[i].getName() == "NULL")
			return;

		numOfMonsters = i + 1;
	}
}
