#include "BattleScene.h"

void BattleScene::InitScene() {
	Monsters mons;
	vector<Monster> monsters{ mons._1, mons._2, mons._3, mons._4, mons._5, mons._6 };

	/*int ranNum = 1296 + 432 + 108 + 24 + 5;
	int curNum = 0;
	for (int i = 6; i >= 1; i--) {
		if (i > 0)
			curNum = ranNum / pow(6, i - 1);
		else
			curNum = ranNum;

		ranNum -= curNum * pow(6, i - 1);
		cout << curNum;
	}
	cout << endl;
	system("pause");*/
	
	auto rng = std::default_random_engine{ static_cast<unsigned int>(rand()) };
	std::shuffle(std::begin(monsters), std::end(monsters), rng);
	party1.name = "Player 1";
	party1.mon[0] = monsters[0];
	party1.mon[1] = monsters[1];
	party1.mon[2] = monsters[2];
	party1.mon[3] = monsters[3];
	party1.mon[4] = monsters[4];
	party1.mon[5] = monsters[5];
	party1.currentMonSlot = 0;

	rng = std::default_random_engine{ static_cast<unsigned int>(rand()) };
	std::shuffle(std::begin(monsters), std::end(monsters), rng);
	party2.name = "Player 2";
	party2.mon[0] = monsters[0];
	party2.mon[1] = monsters[1];
	party2.mon[2] = monsters[2];
	party2.mon[3] = monsters[3];
	party2.mon[4] = monsters[4];
	party2.mon[5] = monsters[5];
	party2.currentMonSlot = 0;
}

void BattleScene::UpdateScene() {
	if (Input::GetKeyDown(VK_ESCAPE)) {
		Game::shared_instance().SwitchToScene(1);
		return;
	}

	if (p1Turn) {
		playerTurn(party1, party2);
		if (party2.GetCurMon()->getHealthCurrent() <= 0) {
			party2.GetCurMon()->alive = false;
			for (int i = 0; i < 6; i++) {
				if (party2.mon[i].alive) {
					party2.currentMonSlot = i;
					break;
				}
			}
		}
	} else {
		playerTurn(party2, party1);
		if (party1.GetCurMon()->getHealthCurrent() <= 0) {
			party1.GetCurMon()->alive = false;
			for (int i = 0; i < 6; i++) {
				if (party1.mon[i].alive) {
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
	for (int x = 0; x < selBack[1][1] + 2; x += selBack[1][1] + 1) {
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
		Game::shared_instance().buffer.WriteBuffer(pCurrent.GetCurMon()->getName(), 10, 3 + x, pCurrent.GetCurMon()->getColor(), true);
		Game::shared_instance().buffer.WriteBuffer("Health:             " + to_string(pCurrent.GetCurMon()->getHealthCurrent()) + "/" + to_string(pCurrent.GetCurMon()->getHealthTotal()) /*+ "   s: " + to_string(pCurrent.GetCurMon()->getSpeedCurrent()) + ", d: " + to_string(pCurrent.GetCurMon()->getdefenceCurrent()) + ", a: " + to_string(pCurrent.GetCurMon()->getAttackCurrent())*/, 0, 4 + x, 7, true);

		string effStr{ "Effects: " };

		for (int i = 0; i < pCurrent.GetCurMon()->getEffects()->size(); i++) {
			effStr += pCurrent.GetCurMon()->getEffect(i)->getEffect();

			if (i < pCurrent.GetCurMon()->getEffects()->size() - 1)
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

		Game::shared_instance().buffer.WriteBuffer(mText, 0, 12 + static_cast<int>(i) * 6, ms[i].getColor());
	}
}

void BattleScene::damageCalculator(Monster *attacker, Monster *defender, Move *attack, int checkType) {
	//damage checks

	string tempStr{ "" };

	//apply the bonus stats again, make sure that it deosnt become an endless recursive function using the 'checkPassive' bool
	if (checkType == 0) {
		damageStr = "\n";
		damageTime = 5;
		if (attacker->getMovePassive()->getCooldownCurrent() == 0) {
			damageCalculator(attacker, defender, attacker->getMovePassive(), 1);
			attacker->getMovePassive()->setCooldownCurrent(attacker->getMovePassive()->getCooldown() + 1);
		}

		if (damageStr == "Passive: ")
			damageStr = "\n";

		if (damageStr == "Passive: Overheat\n") {
			if (attack->getType() == "Fire")
				attacker->addAttackTemp(attacker->getMovePassive()->getPower() / 100.f);
			else
				damageStr = "\n";
		}

		if (damageStr == "Passive: Speedy Water\n") {
			if (attack->getType() == "Water")
				attacker->addEffect(*attacker->getMovePassive());
			else
				damageStr = "\n";
		}

		if (attacker->getEffects()->size() > 0) {
			for (size_t i = 0; i < attacker->getEffects()->size(); i++) {
				if (attacker->getEffect(i)->getLength() > 1)
					damageCalculator(defender, attacker, attacker->getEffect(i), 2);
				
				attacker->getEffect(i)->setLength(attacker->getEffect(i)->getLength() - 1);
				
				if (attacker->getEffect(i)->getLength() <= 0) {
					attacker->removeEffect(i);
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
		if (attack->getEffect() == "Slow Water") {
			damageStr = "Passive: Slow Water\n";
			return;
		}
	}

	//for effects that affect the attacker but not the defender
	if (attack->getSelfEffect()) {
		bool curAcc = rand() % 100 < attacker->getSpeedCurrent() * attack->getAccuracy() / 100;

		if (attack->getEffect() == "Heal" && curAcc) {
			attacker->addHealth(attacker->getHealthTotal() * attack->getPower() / 100.f);
			tempStr += attacker->getName() + " has regenerated it's health!\n";
		}

		if (attack->getEffect() == "Thorns" && curAcc) {
			attacker->addAttackTemp(attack->getPower() / 100.f);
			tempStr += attacker->getName() + " has grown more thorns!\n";
		}

		if (attack->getEffect() == "Block") {
			if (checkType != 2) {
				attacker->addEffect(*attack);
				tempStr += attacker->getName() + " has increased defense!\n";
				attacker->addDefenceTemp(attack->getPower() / 100.f);
			}

			defender->addDefenceTemp(attack->getPower() / 100.f);
		}

		if (attack->getEffect() == "Speed") {
			if (checkType != 2) {
				attacker->addEffect(*attack);
				tempStr += attacker->getName() + " has increased in speed!\n";
				attacker->addSpeedTemp(attack->getPower() / 100.f);
			}

			defender->addSpeedTemp(attack->getPower() / 100.f);
		}

		if (attack->getEffect() == "Sharpen") {
			if (checkType != 2) {
				attacker->addEffect(*attack);
				tempStr += attacker->getName() + " has sharpened its claws!\n";
				attacker->addAttackTemp(attack->getPower() / 100.f);
			}

			defender->addAttackTemp(attack->getPower() / 100.f);
		}

		if (attack->getEffect() == "Speedy Water") {
			defender->addSpeedTemp(attack->getPower() / 100.f);
		}
		//if !someEffect to continue on with standard attacking

		if (checkType != 2)
			damageStr += tempStr;

		return;
	}

	if (checkType != 2) {
		if (rand() % 100 > attack->getAccuracy()* attacker->getSpeedCurrent() / defender->getSpeedCurrent()) {
			if (attack->getEffect() == "Kraken") {
				int atck{ static_cast<int>((1.2 * attacker->getAttackCurrent() / attacker->getdefenceCurrent()) * attack->getPower() * 1.5) };
				attacker->setHealthCurrent(attacker->getHealthCurrent() - atck);
				damageStr += attacker->getName() + " has been attacked by its own kraken!";
				damageStr += "  " + to_string(atck) + " DAMAGE DEALT!\n";
			} else
				damageStr += "MISS!\n";
	
			return;
		}

		//adding effects
		if (attack->getEffect() == "Poision") {
			defender->addEffect(*attack);
			damageStr += defender->getName() + " has been poisioned!\n";
		}

		if (attack->getEffect() == "Bleeding") {
			defender->addEffect(*attack);
			damageStr += defender->getName() + " is now Bleeding!\n";
		}

		if (attack->getEffect() == "Burn") {
			defender->addEffect(*attack);
			damageStr += defender->getName() + " has been set on fire!\n";
		}

		if (attack->getEffect() == "Blind") {
			defender->addEffect(*attack);
			damageStr += defender->getName() + " has been blinded!\n";
		}

		if (attack->getEffect() == "Drowned") {
			defender->addEffect(*attack);
			damageStr += defender->getName() + " has been drowned!\n";
		}

		if (attack->getType() == "Fire" && defender->getMovePassive()->getEffect() == "Overheat")
			defender->getMovePassive()->setCooldownCurrent(1);

		if (attack->getEffect() == "Extreme Heat") {
			defender->addEffect(*attack);
			damageStr += defender->getName() + " has been slowed by the heat wave!\n";
		}

		if (attacker->getMovePassive()->getEffect() == "Slow Water" && attack->getEffect() != "Slow Water") {
			if (attack->getType() == "Water")
				defender->addEffect(*attacker->getMovePassive());
			else
				damageStr = "\n";
		}
	}
	else {
		if (attack->getEffect() == "Blind") {
			defender->addSpeedTemp(-attack->getPower() / 100.f);
			return;
		}
		if (attack->getEffect() == "Extreme Heat") {
			defender->addSpeedTemp(-attack->getPower() / 100.f);
			return;
		}
		if (attack->getEffect() == "Slow Water") {
			defender->addSpeedTemp(-attack->getPower() / 100.f);
			return;
		}
		if (attack->getEffect() == "Drowned") {
			defender->addSpeedTemp(-attack->getPower() / 100.f);
		}
	}

	float damageAdvantage = 0.f;
	if (defender->getType() == "Grass" && attack->getType() == "Fire" || defender->getType() == "Fire" && attack->getType() == "Water" || defender->getType() == "Water" && attack->getType() == "Grass") {
		damageAdvantage += 2.0f;
		tempStr += "SUPER EFFECTIVE HIT!";
	} 
	else if (defender->getType() == "Grass" && attack->getType() == "Water" || defender->getType() == "Fire" && attack->getType() == "Grass" || defender->getType() == "Water" && attack->getType() == "Fire") {
		damageAdvantage += 1.0f;
		tempStr += "WEAK HIT!";
	} 
	else {
		damageAdvantage += 1.5f;
		tempStr += "HIT!";
	}

	int atck{ static_cast<int>((1.2 * attacker->getAttackCurrent() / defender->getdefenceCurrent()) * attack->getPower() * damageAdvantage) };
	defender->setHealthCurrent(defender->getHealthCurrent() - atck);

	if (attack->getEffect() == "Lifesteal") {
		attacker->addHealth(atck);
	}

	tempStr += "  " + to_string(atck) + " DAMAGE DEALT!\n";

	if (checkType != 2)
		damageStr += tempStr;
}

void BattleScene::playerTurn(Party &p1, Party &p2) {
	int selection{ 0 };
	Game::shared_instance().buffer.WriteBuffer(p1.name + " Turn!", 0, 0);

	drawCurrentHealth(party1, party2);

	showPlayerMoves(p1.GetCurMon()->getMoves());

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
			if (p1.GetCurMon()->getMove1()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.GetCurMon()->getMove1()->setCooldownCurrent(p1.GetCurMon()->getMove1()->getCooldown() + 1);
				damageCalculator(p1.GetCurMon(), p2.GetCurMon(), p1.GetCurMon()->getMove1());
			}
			break;
		case 2:
			if (p1.GetCurMon()->getMove2()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.GetCurMon()->getMove2()->setCooldownCurrent(p1.GetCurMon()->getMove2()->getCooldown() + 1);
				damageCalculator(p1.GetCurMon(), p2.GetCurMon(), p1.GetCurMon()->getMove2());
			}
			break;
		case 3:
			if (p1.GetCurMon()->getMove3()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.GetCurMon()->getMove3()->setCooldownCurrent(p1.GetCurMon()->getMove3()->getCooldown() + 1);
				damageCalculator(p1.GetCurMon(), p2.GetCurMon(), p1.GetCurMon()->getMove3());
			}
			break;
		case 4:
			if (p1.GetCurMon()->getMove4()->getCooldownCurrent() == 0) {
				tookTurn = true;
				p1.GetCurMon()->getMove4()->setCooldownCurrent(p1.GetCurMon()->getMove4()->getCooldown() + 1);
				damageCalculator(p1.GetCurMon(), p2.GetCurMon(), p1.GetCurMon()->getMove4());
			}
			break;
		default:
			break;
		}

		if (tookTurn) {
			p1Turn = !p1Turn;
			if (p1.GetCurMon()->getMove1()->getCooldownCurrent() > 0) {
				p1.GetCurMon()->getMove1()->setCooldownCurrent(p1.GetCurMon()->getMove1()->getCooldownCurrent() - 1);
			}
			if (p1.GetCurMon()->getMove2()->getCooldownCurrent() > 0) {
				p1.GetCurMon()->getMove2()->setCooldownCurrent(p1.GetCurMon()->getMove2()->getCooldownCurrent() - 1);
			}
			if (p1.GetCurMon()->getMove3()->getCooldownCurrent() > 0) {
				p1.GetCurMon()->getMove3()->setCooldownCurrent(p1.GetCurMon()->getMove3()->getCooldownCurrent() - 1);
			}
			if (p1.GetCurMon()->getMove4()->getCooldownCurrent() > 0) {
				p1.GetCurMon()->getMove4()->setCooldownCurrent(p1.GetCurMon()->getMove4()->getCooldownCurrent() - 1);
			}
			if (p1.GetCurMon()->getMovePassive()->getCooldownCurrent() > 0) {
				p1.GetCurMon()->getMovePassive()->setCooldownCurrent(p1.GetCurMon()->getMovePassive()->getCooldownCurrent() - 1);
			}
			//reset the attackers bonus stats, if they can still get it the stats will be applied again later on
			p2.GetCurMon()->ResetTemp();
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
