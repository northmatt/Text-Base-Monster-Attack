#pragma once

#include "Game.h"
#include "BattlePlayer.h"
#include "TextBox.h"

using std::round;

class MapLevelCursor : public Entity {
public:
	MapLevelCursor(string inImage, string inName, double inPosX, double inPosY);

	void Update(size_t i) override;
	void LoadMonster(bool _isBoss = false);
	void LoadBattle();
private:
	Vec2 vel;
	Vec2 maxPos;
	double speed{ 8 };
};