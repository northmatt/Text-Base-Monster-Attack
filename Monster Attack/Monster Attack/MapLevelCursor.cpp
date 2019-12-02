#include "MapLevelCursor.h"

MapLevelCursor::MapLevelCursor(string inImage, string inName, double inPosX, double inPosY) {
	pos = Vec2{ 1, 1 };
	image = inImage;
	name = inName;
	maxPos = Vec2{ inPosX, inPosY };

	Monsters mons;
	vector<Monster> monsters{ mons._1, mons._2, mons._3, mons._4, mons._5, mons._6 };

	BattlePlayer* thePlayer = nullptr;
	thePlayer = new BattlePlayer;
	thePlayer->name = "Player 1";
	thePlayer->mon[0] = monsters[rand() % 2];

	thePlayer->currentMonSlot = 0;
	thePlayer->FindNumMons();
	Game::shared_instance().SetMainPlayer(thePlayer);
}

void MapLevelCursor::Update(size_t i) {
	/*if (Input::GetKeyDown(VK_F1)) {
		LoadMonster();
		Game::shared_instance().SwitchToScene(5);
	}

	if (Input::GetKeyDown(VK_F2)) {
		LoadMonster(true);
		Game::shared_instance().SwitchToScene(5);
	}

	if (Input::GetKeyDown(VK_F3)) {
		static_cast<BattlePlayer*>(Game::shared_instance().GetMainPlayer())->healed = false;
	}*/

	//movement
	{
		if (Input::GetKey(37))
			vel.x -= 1;
		if (Input::GetKey(39))
			vel.x += 1;

		if (Input::GetKey(38))
			vel.y -= 1;
		if (Input::GetKey(40))
			vel.y += 1;

		vel = vel.Normalize() * Time::deltaTime;

		if (Input::GetKey(VK_CONTROL))
			vel = vel * 1.5;

		if (vel.x != 0 || vel.y != 0)
			LoadBattle();

		pos.x = pos.x + vel.x * speed;
		if (Game::shared_instance().GetCurrentScene()->colorScreen[round(pos.x - 1) * 2 + round(pos.y - 1) * maxPos.x * 2] == BACKGROUND_BLUE)
			pos.x = pos.x - vel.x * speed;

		pos.y = pos.y + vel.y * speed;
		if (Game::shared_instance().GetCurrentScene()->colorScreen[round(pos.x - 1) * 2 + round(pos.y - 1) * maxPos.x * 2] == BACKGROUND_BLUE)
			pos.y = pos.y - vel.y * speed;

		vel.Zero();

		if (pos.x < 1)
			pos.x = 1;
		else if (pos.x > maxPos.x)
			pos.x = maxPos.x;

		if (pos.y < 1)
			pos.y = 1;
		else if (pos.y > maxPos.y)
			pos.y = maxPos.y;
	}

	if (Game::shared_instance().GetCurrentScene()->colorScreen[round(pos.x - 1) * 2 + round(pos.y - 1) * maxPos.x * 2] == (BACKGROUND_RED | BACKGROUND_BLUE) && static_cast<BattlePlayer*>(Game::shared_instance().GetMainPlayer())->healed == false) {
		static_cast<BattlePlayer*>(Game::shared_instance().GetMainPlayer())->healMons();
		Game::shared_instance().GetCurrentScene()->addEntity(new TextBox("Nuggets have been healed!", 7, 3, Game::shared_instance().buffer.GetCSBI().dwSize.X / 4, Game::shared_instance().buffer.GetCSBI().dwSize.Y / 2));
	}

	Game::shared_instance().buffer.SetCamPos({ static_cast<int>(round(pos.x)), static_cast<int>(round(pos.y)) });
	Game::shared_instance().buffer.WriteBuffer(image, round(pos.x), pos.y, color);
}

void MapLevelCursor::LoadMonster(bool _isBoss) {
	Monsters mons;
	vector<Monster> monsters{ mons._1, mons._2, mons._3, mons._4, mons._5, mons._6 };

	BattlePlayer* theEnemy = nullptr;
	theEnemy = new BattlePlayer;
	theEnemy->name = "Player 2";
//	theEnemy->mon[0] = mons._2;

	if (_isBoss)
		theEnemy->mon[0] = mons._7;
	else {
		int ranNumOfEnemies = rand() % static_cast<BattlePlayer*>(Game::shared_instance().GetMainPlayer())->numOfMonsters + 1;
		int ranNum = rand() % static_cast<int>(pow(6, 6));
		int curNum = 0;
		for (int i = 6; i >= 1; i--) {
			if (i > 0)
				curNum = ranNum / pow(6, i - 1);
			else
				curNum = ranNum;

			ranNum -= curNum * pow(6, i - 1);

			if (i <= ranNumOfEnemies)
				theEnemy->mon[i - 1] = monsters[curNum];
		}
	}

	theEnemy->currentMonSlot = 0;
	Game::shared_instance().SetMainEnemy(theEnemy);
}

void MapLevelCursor::LoadBattle() {
	double ranNumCheck{ 0 };
	int backCol{ 0 };
	bool isBoss{ false };
	backCol = Game::shared_instance().GetCurrentScene()->colorScreen[round(pos.x - 1) * 2 + round(pos.y - 1) * maxPos.x * 2];
	if (backCol == BACKGROUND_GREEN) {
		ranNumCheck = 1;
	} else if (backCol == (BACKGROUND_GREEN | BACKGROUND_INTENSITY)) {
		ranNumCheck = 3;
	} else if (backCol == (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) || backCol == (BACKGROUND_INTENSITY)) {
		ranNumCheck = 8;
		isBoss = true;
	}
	else
		return;

	int ranNum{ rand() % 100 };
	if (ranNum <= ranNumCheck) {
		LoadMonster(isBoss);
		Game::shared_instance().SwitchToScene(5);
	}
}
