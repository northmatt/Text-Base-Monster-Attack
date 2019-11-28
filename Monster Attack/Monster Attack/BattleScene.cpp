#include "BattleScene.h"
#include "TestEntity.h"

void BattleScene::InitScene() {
	//fire
	Move flame_punch("Fire Punch", "None", "Fire", 20, 100, 0, 0, FOREGROUND_RED);
	Move melt_armor("Melt Armor", "Destroy Armor", "Fire", 100, 100, 2, 0, FOREGROUND_RED);
	Move volcanic_shield("Volcanic Shield", "Gain Armor", "Fire", 40, 100, 2, 0, FOREGROUND_RED);
	//grass
	Move grass_punch("Grass Punch", "None", "Grass", 20, 100, 0, 0, FOREGROUND_GREEN);
	Move earth_bombardment("Earth Bombardment", "Destroy Armor", "Grass", 75, 100, 1, 0, FOREGROUND_GREEN);
	Move shell_shield("Shell Shield", "Gain Armor", "Grass", 50, 100, 4, 0, FOREGROUND_GREEN);
	//water
	Move water_punch("Water Punch", "None", "Water", 20, 100, 0, 0, FOREGROUND_BLUE);
	Move tsunami_slam("Tsunami Slam", "Destroy Armor", "Water", 100, 100, 3, 0, FOREGROUND_BLUE);
	//dark
	Move dark_punch("Dark Punch", "None", "Dark", 30, 100, 0, 0, FOREGROUND_INTENSITY);
	Move self_sacrifice("Self Sacrifice", "Self Sacrifice", "Dark", 50, 100, 1, 0, FOREGROUND_INTENSITY);
	Move dark_magic("Dark Magic", "Heal", "Dark", 20, 100, 1, 0, FOREGROUND_INTENSITY);
	Move kill("Kill", "None", "Dark", 10000, 100, 0, 3, FOREGROUND_INTENSITY);
	//light
	Move light_punch("Light Punch", "None", "Light", 30, 100, 0, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	//grass
	Monster _1("Skorpislash", "Grass", "Light", 101, 70, 70, 80, FOREGROUND_GREEN, grass_punch, shell_shield, earth_bombardment, kill);
	Monster _2("Pigeonite", "Grass", "Dark", 82, 80, 80, 80, FOREGROUND_GREEN, grass_punch, dark_punch, flame_punch, kill);
	Monster _3("Irobug", "Grass", "Light", 102, 70, 150, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, grass_punch, light_punch, earth_bombardment, kill);
	Monster _4("Slowphant", "Grass", "Dark", 81, 80, 80, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, grass_punch, light_punch, flame_punch, kill);
	//fire
	Monster _5("Skeleking", "Fire", "Light", 20, 100, 190, 40, FOREGROUND_RED, flame_punch, dark_punch, self_sacrifice, dark_magic);
	Monster _6("Flamepie", "Fire", "Dark", 83, 80, 80, 80, FOREGROUND_RED, flame_punch, dark_punch, flame_punch, kill);
	Monster _7("Dragithe", "Fire", "Light", 105, 70, 70, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, flame_punch, light_punch, volcanic_shield, kill);
	Monster _8("Pheonix", "Fire", "Dark", 86, 80, 80, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, flame_punch, light_punch, melt_armor, kill);
	//water
	Monster _9("Quilling", "Water", "Light", 104, 70, 70, 80, FOREGROUND_GREEN, water_punch, dark_punch, flame_punch, kill);
	Monster _10("Gladiawhale", "Water", "Dark", 85, 80, 80, 80, FOREGROUND_GREEN, water_punch, dark_punch, flame_punch, kill);
	Monster _11("Penguinite", "Water", "Light", 103, 70, 70, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, water_punch, light_punch, flame_punch, kill);
	Monster _12("Oystora", "Water", "Dark", 84, 80, 80, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, water_punch, light_punch, tsunami_slam, kill);

	party1.name = "Player 1";
	party1.mon[0] = _5;
	party1.mon[1] = _3;
	party1.mon[2] = _1;
	party1.mon[3] = _7;
	party1.mon[4] = _9;
	party1.mon[5] = _11;
	party1.currentMon = party1.mon[0];
	party1.currentMonSlot = 0;

	party2.name = "Player 2";
	party2.mon[0] = _8;
	party2.mon[1] = _12;
	party2.mon[2] = _10;
	party2.mon[3] = _6;
	party2.mon[4] = _4;
	party2.mon[5] = _2;
	party2.currentMon = party2.mon[0];
	party2.currentMonSlot = 0;
}

void BattleScene::UpdateScene() {
	if (p1Turn) {
		playerTurn(party1, party2);
		if (party2.currentMon.getHealthCurrent() <= 0) {
			party2.mon[party2.currentMonSlot].alive = false;
			for (int i = 0; i < 6; i++) {
				if (party2.mon[i].alive) {
					party2.currentMon = party2.mon[i];
					party2.currentMonSlot = i;
					break;
				}
			}
		}
	} else {
		playerTurn(party2, party1);
		if (party1.currentMon.getHealthCurrent() <= 0) {
			party1.mon[party1.currentMonSlot].alive = false;
			for (int i = 0; i < 6; i++) {
				if (party1.mon[i].alive) {
					party1.currentMon = party1.mon[i];
					party1.currentMonSlot = i;
					break;
				}
			}
		}
	}
}

void BattleScene::drawCurrentHealth(Party p1, Party p2) {
	//({0, 2}, {15, 4})		({0, 6}, {15, 8})
	vector<vector<int>> selBack{ {0, 2}, {40, 3} };

	if (!p1Turn)
		selBack[0][1] += 4;

	string selBackHorz = string(selBack[1][0], ' ');
	string selBackRect{ "" };

	for (size_t i = 0; i < selBack[1][1]; i++)
		selBackRect += selBackHorz + "\n";

	Game::shared_instance().buffer.WriteBuffer(selBackRect, selBack[0][0], selBack[0][1], BACKGROUND_INTENSITY);

	Game::shared_instance().buffer.WriteBuffer(p1.name + ":", 0, 2, 7, true);
	for (int i = 0; i < 6; i++) {
		if (p1.mon[i].alive == true) {
			Game::shared_instance().buffer.WriteBuffer("o", 10 + i, 2, p1.mon[i].getColor(), true);
		} else {
			Game::shared_instance().buffer.WriteBuffer(".", 10 + i, 2, p1.mon[i].getColor(), true);
		}
	}
	Game::shared_instance().buffer.WriteBuffer("Current Monster:", 0, 3, 7, true);
	Game::shared_instance().buffer.WriteBuffer(p1.currentMon.getName(), 10, 3, p1.currentMon.getColor(), true);
	Game::shared_instance().buffer.WriteBuffer("Health:             " + to_string(p1.currentMon.getHealthCurrent()) + "/" + to_string(p1.currentMon.getHealthTotal()), 0, 4, 7, true);

	Game::shared_instance().buffer.WriteBuffer(p2.name + ":", 0, 6, 7, true);
	for (int i = 0; i < 6; i++) {
		if (p2.mon[i].alive == true) {
			Game::shared_instance().buffer.WriteBuffer("o", 10 + i, 6, p2.mon[i].getColor(), true);
		} else {
			Game::shared_instance().buffer.WriteBuffer(".", 10 + i, 6, p2.mon[i].getColor(), true);
		}
	}
	Game::shared_instance().buffer.WriteBuffer("Current Monster:", 0, 7, 7, true);
	Game::shared_instance().buffer.WriteBuffer(p2.currentMon.getName(), 10, 7, p2.currentMon.getColor(), true);
	Game::shared_instance().buffer.WriteBuffer("Health:             " + to_string(p2.currentMon.getHealthCurrent()) + "/" + to_string(p2.currentMon.getHealthTotal()), 0, 8, 7, true);
}

void BattleScene::showPlayerMoves(vector<Move> ms) {
	for (size_t i = 0; i < ms.size(); i++) {
		string mText{ "" };

		mText += ms[i].getName() + "\nPower: " + to_string(ms[i].getPower()) + "\nAccuracy: " + to_string(ms[i].getAccuracy()) + '\n';
			
		if (ms[i].getCooldown() > 0)
			mText += to_string(ms[i].getCooldown()) + " Turn Cooldown";
		else if (ms[i].getCooldown() == 0)
			mText += "No Cooldown";
		else
			mText += "Passive Ability";

		Game::shared_instance().buffer.WriteBuffer(mText, 0, 10 + i * 5, ms[i].getColor());
	}
}

void BattleScene::damageCalculator(Monster &attacker, Monster &defender, Move attack, bool checkPassive) {
	//damage checks

	damageStr = "\n";
	damageTime = 2;

	if (attacker.getPassiveReset() > 0 && checkPassive) {
		damageCalculator(attacker, defender, attacker.getMovePassive(), false);
	}

	//effect application
	if (attack.getEffect() == "Destroy Armor") {
		defender.setDefenceCurrent(defender.getdefenceCurrent() * 0.7);

		damageStr = attacker.getName() + " has broken " + defender.getName() + "'s armor!\n";
	}
	if (attack.getEffect() == "Gain Armor") {
		attacker.setDefenceCurrent(attacker.getdefenceCurrent() * 1.2);

		damageStr = attacker.getName() + " has built up its armor!\n";
	}

	if (attack.getEffect() == "Self Sacrifice") {
		attacker.setHealthCurrent(attacker.getHealthCurrent() / 1.5);
		attacker.setAttackCurrent(attacker.getAttackCurrent() * 2);

		damageStr = attacker.getName() + " has drained it's own life!\n";
	}

	if (attack.getEffect() == "Heal") {
		attacker.setHealthCurrent(min(attacker.getHealthCurrent() + attacker.getHealthTotal() / 2.7, attacker.getHealthTotal()));

		damageStr = attacker.getName() + " has regenerated it's health!\n";
	}

	bool accuracycheck = false;
	int damageAdvantage = 0.f;
	if (rand() % 100 <= attack.getAccuracy()) {
		accuracycheck = true;
		if (defender.getType() == "Grass" && attack.getType() == "Fire" || defender.getType() == "Fire" && attack.getType() == "Water" || defender.getType() == "Water" && attack.getType() == "Grass") {
			damageAdvantage += 2.0f;
			damageStr += "SUPER EFFECTIVE HIT!";
		} else if (defender.getType() == "Grass" && attack.getType() == "Water" || defender.getType() == "Fire" && attack.getType() == "Grass" || defender.getType() == "Water" && attack.getType() == "Fire") {
			damageAdvantage += 1.0f;
			damageStr += "WEAK HIT!";
		} else {
			damageAdvantage += 1.5f;
			damageStr += "HIT!";
		}
	} else
		damageStr = "MISS!";

	if (accuracycheck) {
		int atck{ static_cast<int>((1.2 * attacker.getAttackCurrent() / defender.getdefenceCurrent()) * attack.getPower() * damageAdvantage) };
		defender.setHealthCurrent(defender.getHealthCurrent() - atck);
		damageStr += "\n" + to_string(atck) + " DAMAGE DEALT!";
	}
}

void BattleScene::playerTurn(Party &p1, Party &p2) {
	int selection{ 0 };
	Game::shared_instance().buffer.WriteBuffer(p1.name + " Turn!", 0, 0);

	drawCurrentHealth(party1, party2);

	showPlayerMoves(p1.currentMon.getMoves());

	Game::shared_instance().buffer.WriteBuffer("Select move: ", 0, 30);

	if (Input::GetKeyDown('1') || Input::GetKeyDown(VK_NUMPAD1))
		selection = 1;
	if (Input::GetKeyDown('2') || Input::GetKeyDown(VK_NUMPAD2))
		selection = 2;
	if (Input::GetKeyDown('3') || Input::GetKeyDown(VK_NUMPAD3))
		selection = 3;
	if (Input::GetKeyDown('4') || Input::GetKeyDown(VK_NUMPAD4))
		selection = 4;

	if (1 <= selection && selection <= 4) {
		bool tookTurn = false;

		switch (selection) {
		case 1:
			if (p1.currentMon.getMove1()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove1()->setCooldownCurrent(p1.currentMon.getMove1()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, *p1.currentMon.getMove1());
				
				if (p1.currentMon.getMove1()->getLength() > 1) {
					p1.currentMon.setMovePassive(*p1.currentMon.getMove1());
					p1.currentMon.setPassiveReset(p1.currentMon.getMove1()->getLength() + 1);
				}
			}
			break;
		case 2:
			if (p1.currentMon.getMove2()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove2()->setCooldownCurrent(p1.currentMon.getMove2()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, *p1.currentMon.getMove2());

				if (p1.currentMon.getMove2()->getLength() > 1) {
					p1.currentMon.setMovePassive(*p1.currentMon.getMove2());
					p1.currentMon.setPassiveReset(p1.currentMon.getMove2()->getLength());
				}
			}
			break;
		case 3:
			if (p1.currentMon.getMove3()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove3()->setCooldownCurrent(p1.currentMon.getMove3()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, *p1.currentMon.getMove3());

				if (p1.currentMon.getMove3()->getLength() > 1) {
					p1.currentMon.setMovePassive(*p1.currentMon.getMove3());
					p1.currentMon.setPassiveReset(p1.currentMon.getMove3()->getLength() + 1);
				}
			}
			break;
		case 4:
			if (p1.currentMon.getMove4()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove4()->setCooldownCurrent(p1.currentMon.getMove1()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, *p1.currentMon.getMove4());

				if (p1.currentMon.getMove4()->getLength() > 1) {
					p1.currentMon.setMovePassive(*p1.currentMon.getMove4());
					p1.currentMon.setPassiveReset(p1.currentMon.getMove4()->getLength() + 1);
				}
			}
			break;
		default:
			break;
		}

		if (tookTurn) {
			p1Turn = !p1Turn;
			if (p1.currentMon.getMove1()->getCooldownCurrent() > 0) {
				p1.currentMon.getMove1()->setCooldownCurrent(p1.currentMon.getMove1()->getCooldownCurrent() - 1);
			}
			if (p1.currentMon.getMove2()->getCooldownCurrent() > 0) {
				p1.currentMon.getMove2()->setCooldownCurrent(p1.currentMon.getMove2()->getCooldownCurrent() - 1);
			}
			if (p1.currentMon.getMove3()->getCooldownCurrent() > 0) {
				p1.currentMon.getMove3()->setCooldownCurrent(p1.currentMon.getMove3()->getCooldownCurrent() - 1);
			}
			if (p1.currentMon.getMove4()->getCooldownCurrent() > 0) {
				p1.currentMon.getMove4()->setCooldownCurrent(p1.currentMon.getMove4()->getCooldownCurrent() - 1);
			}
			if (p1.currentMon.getPassiveReset() > 0) {
				p1.currentMon.setPassiveReset(p1.currentMon.getPassiveReset() - 1);

				if (p1.currentMon.getPassiveReset() == 0) {
					p1.currentMon.setMovePassive(Move());
				}
			}
		}
	}

	if (damageTime > 0) {
		Game::shared_instance().buffer.WriteBuffer(damageStr, 0, 32);
		damageTime -= Time::deltaTime;
	}
	else {
		damageTime = 0;
		damageStr = "";
	}
}
