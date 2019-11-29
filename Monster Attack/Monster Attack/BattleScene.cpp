#include "BattleScene.h"
#include "TestEntity.h"

void BattleScene::InitScene() {
	//grass
	Move Photosynthesis("Photosynthesis", "Heal", "Grass", true, 40, 100, 0, 0, FOREGROUND_GREEN);
	Move Whip("Quick Whip", "None", "Grass", false, 40, 100, 0, 0, FOREGROUND_GREEN);
	Move Berries("Poison Berries", "Poision", "Grass", false, 20, 70, 4, 3, FOREGROUND_GREEN);
	Move Thorns("Thorns", "Thorns", "Grass", true, 40, 80, 0, 0, FOREGROUND_GREEN);
	Move ThornThrow("Thorn Throw", "None", "Grass", false, 150, 80, 5, 0, FOREGROUND_GREEN);
	Move VineBlock("Vine Block", "Block", "Grass", true, 50, 90, 2, 2, FOREGROUND_GREEN);

	//fire
	Move BurnTouch("Burn Touch", "Burn", "Fire", false, 20, 30, 2, 1, FOREGROUND_RED);
	Move FireCircle("Fire Circle", "None", "Fire", false, 40, 100, 0, 0, FOREGROUND_RED);
	Move FireSpin("Fire Spin", "Burn", "Fire", false, 25, 90, 4, 2, FOREGROUND_RED);
	Move Overheat("Overheat", "Overheat", "Fire", true, 75, 100, 0, 0, FOREGROUND_RED);
	Move ShadowFire("Shadow Fire", "None", "Fire", false, 150, 80, 5, 0, FOREGROUND_RED);
	Move HeatWave("Heat Wave", "Extreme Heat", "Fire", false, 10, 80, 3, 2, FOREGROUND_RED);

	//water
	Move GoodCurrent("Good Current", "Speedy Water", "Water", true, 10, 100, 0, 3, FOREGROUND_BLUE);
	Move RainStorm("Rain Storm", "None", "Water", false, 40, 100, 0, 0, FOREGROUND_BLUE);
	Move Surf("Surf", "Speed", "Water", true, 20, 100, 2, 2, FOREGROUND_BLUE);
	Move MuddyWater("Muddy Water", "SlowWater", "Water", false, 0, 100, 99999, 0, FOREGROUND_BLUE);
	Move StormyNight("Stormy Night", "None", "Water", false, 40, 100, 0, 0, FOREGROUND_BLUE);
	Move Drown("Drown", "Slow", "Water", false, 0, 90, 3, 2, FOREGROUND_BLUE);

	//dark
	Move LettuceScythe("Lettuce Scythe", "None", "Dark", false, 40, 100, 0, 0, FOREGROUND_INTENSITY);
	Move ThornCage("Thorn Cage", "Bleeding", "Dark", false, 17, 80, 4, 3, FOREGROUND_INTENSITY);
	Move ShadowClaw("Shadow Claw", "None", "Dark", false, 40, 100, 0, 0, FOREGROUND_INTENSITY);
	Move Shroud("Shroud", "Speed", "Dark", true, 20, 100, 2, 2, FOREGROUND_INTENSITY);
	Move KrakenSummon("Kraken Summon", "Kraken", "Dark", false, 350, 30, 0, 0, FOREGROUND_INTENSITY);
	Move Sharpen("Sharpen", "Sharpen", "Dark", true, 0, 100, 2, 1, FOREGROUND_INTENSITY);

	//light
	Move Beam("Beam of Light", "None", "Light", false, 120, 90, 5, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Move Kale("Kimble Kale", "Heal", "Light", true, 3, 100, 7, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Move BlazingSun("Blazing Sun", "None", "Light", false, 120, 90, 5, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Move BlindingLight("Blinding Light", "Blind", "Light", false, 50, 100, 2, 2, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Move ThunderStorm("Thunder Storm", "None", "Light", false, 150, 80, 5, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Move SuctionCups("Suction Cups", "Lifesteal", "Light", false, 30, 90, 2, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	//monsters
	Monster _1("Nugget Lord", "Grass", "Light", 100, 50, 100, 50, FOREGROUND_GREEN | FOREGROUND_INTENSITY, Beam, Whip, Berries, Kale, Photosynthesis);
	Monster _2("Grim Nugget", "Grass", "Dark", 50, 120, 80, 50, FOREGROUND_GREEN, ThornThrow, LettuceScythe, ThornCage, VineBlock, Thorns);
	Monster _3("Kayle", "Fire", "Light", 60, 90, 70, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, BlazingSun, FireCircle, FireSpin, BlindingLight, BurnTouch);
	Monster _4("Doomhound", "Fire", "Dark", 130, 40, 90, 40, FOREGROUND_RED, ShadowFire, ShadowClaw, HeatWave, Shroud, Overheat);
	Monster _5("Squsher", "Water", "Light", 65, 100, 95, 40, FOREGROUND_BLUE | FOREGROUND_INTENSITY, ThunderStorm, RainStorm, SuctionCups, Surf, GoodCurrent);
	Monster _6("Scubabear", "Water", "Dark", 60, 60, 120, 60, FOREGROUND_BLUE, KrakenSummon, StormyNight, Drown, Sharpen, MuddyWater);

	//grass
	/*Monster _1("Skorpislash", "Grass", "Light", 101, 70, 70, 80, FOREGROUND_GREEN, grass_punch, shell_shield, earth_bombardment, kill, light_punch);
	Monster _2("Pigeonite", "Grass", "Dark", 82, 80, 80, 80, FOREGROUND_GREEN, grass_punch, dark_punch, flame_punch, kill, light_punch);
	Monster _3("Irobug", "Grass", "Light", 102, 70, 150, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, grass_punch, light_punch, earth_bombardment, kill, light_punch);
	Monster _4("Slowphant", "Grass", "Dark", 81, 80, 80, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, grass_punch, light_punch, flame_punch, kill, light_punch);
	//fire
	Monster _5("Skeleking", "Fire", "Light", 20, 100, 190, 40, FOREGROUND_RED, flame_punch, dark_punch, self_sacrifice, dark_magic, light_punch);
	Monster _6("Flamepie", "Fire", "Dark", 83, 80, 80, 80, FOREGROUND_RED, flame_punch, dark_punch, flame_punch, kill, light_punch);
	Monster _7("Dragithe", "Fire", "Light", 105, 70, 70, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, flame_punch, light_punch, volcanic_shield, kill, light_punch);
	Monster _8("Pheonix", "Fire", "Dark", 86, 80, 80, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, flame_punch, light_punch, melt_armor, superPower, Photosynthesis);
	//water
	Monster _9("Quilling", "Water", "Light", 104, 70, 70, 80, FOREGROUND_GREEN, water_punch, dark_punch, flame_punch, kill, light_punch);
	Monster _10("Gladiawhale", "Water", "Dark", 85, 80, 80, 80, FOREGROUND_GREEN, water_punch, dark_punch, flame_punch, kill, light_punch);
	Monster _11("Penguinite", "Water", "Light", 103, 70, 70, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, water_punch, light_punch, flame_punch, kill, light_punch);
	Monster _12("Oystora", "Water", "Dark", 84, 80, 80, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, water_punch, light_punch, tsunami_slam, kill, light_punch);*/

	party1.name = "Player 1";
	party1.mon[0] = _5;
	party1.mon[1] = _5;
	party1.mon[2] = _1;
	party1.mon[3] = _2;
	party1.mon[4] = _6;
	party1.mon[5] = _4;
	party1.currentMon = party1.mon[0];
	party1.currentMonSlot = 0;

	party2.name = "Player 2";
	party2.mon[0] = _5;
	party2.mon[1] = _1;
	party2.mon[2] = _5;
	party2.mon[3] = _6;
	party2.mon[4] = _4;
	party2.mon[5] = _3;
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
	vector<vector<int>> selBack{ {0, 2}, {40, 4} };

	if (!p1Turn)
		selBack[0][1] += selBack[1][1] + 1;

	string selBackHorz = string(selBack[1][0], ' ');
	string selBackRect{ "" };

	for (size_t i = 0; i < selBack[1][1]; i++)
		selBackRect += selBackHorz + "\n";

	Game::shared_instance().buffer.WriteBuffer(selBackRect, selBack[0][0], selBack[0][1], BACKGROUND_INTENSITY);

	Party parties[2]{ p1, p2 };
	for (size_t x = 0; x < selBack[1][1] + 2; x += selBack[1][1] + 1) {
		Party pCurrent = parties[x / (selBack[1][1] + 1)];
		Game::shared_instance().buffer.WriteBuffer(pCurrent.name + ":", 0, 2 + x, 7, true);
		for (int i = 0; i < 6; i++) {
			if (pCurrent.mon[i].alive == true) {
				Game::shared_instance().buffer.WriteBuffer("o", 10 + i, 2 + x, pCurrent.mon[i].getColor(), true);
			} else {
				Game::shared_instance().buffer.WriteBuffer(".", 10 + i, 2 + x, pCurrent.mon[i].getColor(), true);
			}
		}
		Game::shared_instance().buffer.WriteBuffer("Current Monster:", 0, 3 + x, 7, true);
		Game::shared_instance().buffer.WriteBuffer(pCurrent.currentMon.getName(), 10, 3 + x, pCurrent.currentMon.getColor(), true);
		Game::shared_instance().buffer.WriteBuffer("Health:             " + to_string(pCurrent.currentMon.getHealthCurrent()) + "/" + to_string(pCurrent.currentMon.getHealthTotal()) + "   s: " + to_string(pCurrent.currentMon.getSpeedCurrent()) + ", d: " + to_string(pCurrent.currentMon.getdefenceCurrent()) + ", a: " + to_string(pCurrent.currentMon.getAttackCurrent()), 0, 4 + x, 7, true);

		string effStr{ "Effects: " };

		for (size_t i = 0; i < pCurrent.currentMon.getEffects()->size(); i++) {
			effStr += pCurrent.currentMon.getEffect(i)->getEffect();

			if (i < pCurrent.currentMon.getEffects()->size() - 1)
				effStr += ", ";
		}

		Game::shared_instance().buffer.WriteBuffer(effStr, 0, 5 + x, 7, true);
	}
}

void BattleScene::showPlayerMoves(vector<Move> ms) {
	for (size_t i = 0; i < ms.size() - 1; i++) {
		string mText{ "" };

		mText += ms[i].getName() + "\nPower: " + to_string(ms[i].getPower()) + "\nAccuracy: " + to_string(ms[i].getAccuracy()) + '\n';
		
		if (ms[i].getCooldownCurrent() > 0)
			mText += to_string(ms[i].getCooldownCurrent()) + " Turns until cooldown expires\n";
		else if (ms[i].getCooldown() > 0)
			mText += to_string(ms[i].getCooldown()) + " Turn Cooldown\n";
		else if (ms[i].getCooldown() == 0)
			mText += "No Cooldown\n";

		mText += "Effect: " + ms[i].getEffect();

		Game::shared_instance().buffer.WriteBuffer(mText, 0, 12 + i * 6, ms[i].getColor());
	}
}

void BattleScene::damageCalculator(Monster &attacker, Monster &defender, Move *attack, int checkType) {
	//damage checks

	string tempStr{ "" };

	//apply the bonus stats again, make sure that it deosnt become an endless recursive function using the 'checkPassive' bool
	if (checkType == 0) {
		damageStr = "\n";
		damageTime = 5;
		if (attacker.getMovePassive()->getCooldownCurrent() == 0) {
			damageCalculator(attacker, defender, attacker.getMovePassive(), 1);
			attacker.getMovePassive()->setCooldownCurrent(attacker.getMovePassive()->getCooldown() + 1);
		}

		if (damageStr == "Passive: ")
			damageStr = "\n";

		if (damageStr == "Passive: Overheat\n") {
			if (attack->getType() == "Fire")
				attacker.addAttackTemp(attacker.getMovePassive()->getPower() / 100.f);
			else
				damageStr = "\n";
		}

		if (damageStr == "Passive: Speedy Water\n") {
			if (attack->getType() == "Water")
				attacker.addEffect(*attacker.getMovePassive());
			else
				damageStr = "\n";
		}

		if (attacker.getEffects()->size() > 0) {
			for (size_t i = 0; i < attacker.getEffects()->size(); i++) {
				if (attacker.getEffect(i)->getLength() > 1)
					damageCalculator(defender, attacker, attacker.getEffect(i), 2);
				
				attacker.getEffect(i)->setLength(attacker.getEffect(i)->getLength() - 1);
				
				if (attacker.getEffect(i)->getLength() <= 0) {
					attacker.removeEffect(i);
					i--;
				}
			}
		}

		damageStr += "Attack: ";
	}
	else if (checkType == 1) {
		damageStr = "Passive: ";

		if (attack->getEffect() == "Overheat") {
			damageStr = "Passive: Overheat\n";
			return;
		}
		if (attack->getEffect() == "Speedy Water") {
			damageStr = "Passive: Speedy Water\n";
			return;
		}
	}

	//for effects that affect the attacker but not the defender
	if (attack->getSelfEffect()) {
		bool curAcc = rand() % 100 < attacker.getSpeedCurrent() * attack->getAccuracy() / 100;

		if (attack->getEffect() == "Heal" && curAcc) {
			attacker.addHealth(attacker.getHealthTotal() * attack->getPower() / 100);
			tempStr += attacker.getName() + " has regenerated it's health!\n";
		}

		if (attack->getEffect() == "Thorns" && curAcc) {
			attacker.addAttackTemp(attack->getPower() / 100.f);
			tempStr += attacker.getName() + " has grown more thorns!\n";
		}

		if (attack->getEffect() == "Block") {
			if (checkType != 2) {
				attacker.addEffect(*attack);
				tempStr += attacker.getName() + " has increased defense\n";
				attacker.addDefenceTemp(attack->getPower() / 100.f);
			}

			defender.addDefenceTemp(attack->getPower() / 100.f);
		}

		if (attack->getEffect() == "Speed") {
			if (checkType != 2) {
				attacker.addEffect(*attack);
				tempStr += attacker.getName() + " has increased in speed\n";
				attacker.addSpeedTemp(attack->getPower() / 100.f);
			}

			defender.addSpeedTemp(attack->getPower() / 100.f);
		}

		if (attack->getEffect() == "Speedy Water") {
			defender.addSpeedTemp(attack->getPower() / 100.f);
		}
		//if !someEffect to continue on with standard attacking

		if (checkType != 2)
			damageStr += tempStr;

		return;
	}

	if (checkType != 2) {
		if (rand() % 100 > attack->getAccuracy()* attacker.getSpeedCurrent() / defender.getSpeedCurrent()) {
			damageStr += "MISS!\n";
			return;
		}

		//adding effects
		if (attack->getEffect() == "Poision") {
			defender.addEffect(*attack);
			damageStr += defender.getName() + " has been poisioned\n";
		}

		if (attack->getEffect() == "Bleeding") {
			defender.addEffect(*attack);
			damageStr += defender.getName() + " is now Bleeding\n";
		}

		if (attack->getEffect() == "Burn") {
			defender.addEffect(*attack);
			damageStr += defender.getName() + " has been set on fire\n";
		}

		if (attack->getEffect() == "Blind") {
			defender.addEffect(*attack);
			damageStr += defender.getName() + " has been blinded\n";
		}

		if (attack->getType() == "Fire" && defender.getMovePassive()->getEffect() == "Overheat")
			defender.getMovePassive()->setCooldownCurrent(1);

		if (attack->getEffect() == "Extreme Heat") {
			defender.addEffect(*attack);
			damageStr += defender.getName() + " has been slowed by the heat wave\n";
		}
	}
	else {
		if (attack->getEffect() == "Blind") {
			defender.addSpeedTemp(-attack->getPower() / 100.f);
			return;
		}
		if (attack->getEffect() == "Extreme Heat") {
			defender.addSpeedTemp(-attack->getPower() / 100.f);
			return;
		}
	}

	int damageAdvantage = 0.f;
	if (defender.getType() == "Grass" && attack->getType() == "Fire" || defender.getType() == "Fire" && attack->getType() == "Water" || defender.getType() == "Water" && attack->getType() == "Grass") {
		damageAdvantage += 2.0f;
		tempStr += "SUPER EFFECTIVE HIT!";
	} 
	else if (defender.getType() == "Grass" && attack->getType() == "Water" || defender.getType() == "Fire" && attack->getType() == "Grass" || defender.getType() == "Water" && attack->getType() == "Fire") {
		damageAdvantage += 1.0f;
		tempStr += "WEAK HIT!";
	} 
	else {
		damageAdvantage += 1.5f;
		tempStr += "HIT!";
	}

	int atck{ static_cast<int>((1.2 * attacker.getAttackCurrent() / defender.getdefenceCurrent()) * attack->getPower() * damageAdvantage) };
	defender.setHealthCurrent(defender.getHealthCurrent() - atck);

	if (attack->getEffect() == "Lifesteal") {
		attacker.addHealth(atck);
	}

	tempStr += "  " + to_string(atck) + " DAMAGE DEALT!\n";

	if (checkType != 2)
		damageStr += tempStr;
}

void BattleScene::playerTurn(Party &p1, Party &p2) {
	int selection{ 0 };
	Game::shared_instance().buffer.WriteBuffer(p1.name + " Turn!", 0, 0);

	drawCurrentHealth(party1, party2);

	showPlayerMoves(p1.currentMon.getMoves());

	Game::shared_instance().buffer.WriteBuffer("Select move: ", 0, 36);

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
				damageCalculator(p1.currentMon, p2.currentMon, p1.currentMon.getMove1());
			}
			break;
		case 2:
			if (p1.currentMon.getMove2()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove2()->setCooldownCurrent(p1.currentMon.getMove2()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, p1.currentMon.getMove2());
			}
			break;
		case 3:
			if (p1.currentMon.getMove3()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove3()->setCooldownCurrent(p1.currentMon.getMove3()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, p1.currentMon.getMove3());
			}
			break;
		case 4:
			if (p1.currentMon.getMove4()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.currentMon.getMove4()->setCooldownCurrent(p1.currentMon.getMove4()->getCooldown() + 1);
				damageCalculator(p1.currentMon, p2.currentMon, p1.currentMon.getMove4());
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
			if (p1.currentMon.getMovePassive()->getCooldownCurrent() > 0) {
				p1.currentMon.getMovePassive()->setCooldownCurrent(p1.currentMon.getMovePassive()->getCooldownCurrent() - 1);
			}
			//reset the attackers bonus stats, if they can still get it the stats will be applied again later on
			p2.currentMon.ResetTemp();
		}
	}

	if (damageTime > 0) {
		Game::shared_instance().buffer.WriteBuffer(damageStr, 0, 38);
		damageTime -= Time::deltaTime;
	}
	else {
		damageTime = 0;
		damageStr = "";
	}
}
