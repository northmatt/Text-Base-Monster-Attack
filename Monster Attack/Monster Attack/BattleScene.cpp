#include "BattleScene.h"
#include "TestEntity.h"

void BattleScene::InitScene() {
	//fire
	Move flame_punch("Fire Punch", "None", "Fire", 20, 100, 1, 7);
	Move melt_armor("Melt Armor", "Destroy Armor", "Fire", 100, 100, 2, 7);
	Move volcanic_shield("Volcanic Shield", "Gain Armor", "Fire", 40, 100, 2,  7);
	//grass
	Move grass_punch("Grass Punch", "None", "Grass", 20, 100, 1, 7);
	Move earth_bombardment("Earth Bombardment", "Destroy Armor", "Grass", 75, 100, 2, 7);
	Move shell_shield("Shell Shield", "Gain Armor", "Grass", 50, 100, 4, 7);
	//water
	Move water_punch("Water Punch", "None", "Water", 20, 100, 1, 7);
	Move tsunami_slam("Tsunami Slam", "Destroy Armor", "Water", 100, 100, 3, 7);
	//dark
	Move dark_punch("Dark Punch", "None", "Dark", 30, 100, 1, 7);
	Move self_sacrifice("Self Sacrifice", "Self Sacrifice", "Dark", 50, 100, 1, 7);
	Move dark_magic("Dark Magic", "Heal", "Dark", 20, 100, 1, 7);
	Move kill("Kill", "None", "Dark", 10000, 100, 1, 7);
	//light
	Move light_punch("Light Punch", "None", "Light", 30, 100, 1, 7);

	//grass
	Monster _1("Skorpislash", "Grass", 101, 70, 70, 80, 7, grass_punch, shell_shield, earth_bombardment, kill);
	Monster _2("Pigeonite", "Grass", 82, 80, 80, 80, 7, grass_punch, dark_punch, flame_punch, kill);
	Monster _3("Irobug", "Grass", 102, 70, 150, 80, 7, grass_punch, light_punch, earth_bombardment, kill);
	Monster _4("Slowphant", "Grass", 81, 80, 80, 80, 7, grass_punch, light_punch, flame_punch, kill);
	//fire
	Monster _5("Skeleking", "Fire", 20, 100, 190, 40, 7, flame_punch, dark_punch, self_sacrifice, dark_magic);
	Monster _6("Flamepie", "Fire", 83, 80, 80, 80, 7, flame_punch, dark_punch, flame_punch, kill);
	Monster _7("Dragithe", "Fire", 105, 70, 70, 80, 7, flame_punch, light_punch, volcanic_shield, kill);
	Monster _8("Pheonix", "Fire", 86, 80, 80, 80, 7, flame_punch, light_punch, melt_armor, kill);
	//water
	Monster _9("Quilling", "Water", 104, 70, 70, 80, 7, water_punch, dark_punch, flame_punch, kill);
	Monster _10("Gladiawhale", "Water", 85, 80, 80, 80, 7, water_punch, dark_punch, flame_punch, kill);
	Monster _11("Penguinite", "Water", 103, 70, 70, 80, 7, water_punch, light_punch, flame_punch, kill);
	Monster _12("Oystora", "Water", 84, 80, 80, 80, 7, water_punch, light_punch, tsunami_slam, kill);

	party1.mon[0] = _5;
	party1.mon[1] = _3;
	party1.mon[2] = _1;
	party1.mon[3] = _7;
	party1.mon[4] = _9;
	party1.mon[5] = _11;
	party1.currentMon = party1.mon[0];
	party1.currentMonSlot = 0;

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
	party2.currentMon.setHealthCurrent(playerTurn(true, party1.currentMon, party2.currentMon));
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
	Sleep(2000);
	party1.currentMon.setHealthCurrent(playerTurn(false, party2.currentMon, party1.currentMon));
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
	Sleep(2000);
}

void BattleScene::drawCurrentHealth(Party p1, Party p2) {
	Game::shared_instance().buffer.WriteBuffer("Player 1:", 0, 2);
	for (int i = 0; i < 6; i++) {
		if (p1.mon[i].alive == true) {
			Game::shared_instance().buffer.WriteBuffer("o", 10 + i * 2, 2, p1.mon[i].getColor());
		} else {
			Game::shared_instance().buffer.WriteBuffer(".", 10 + i * 2, 2, p1.mon[i].getColor());
		}
	}
	Game::shared_instance().buffer.WriteBuffer("Current Monster:", 0, 3);
	Game::shared_instance().buffer.WriteBuffer(p1.currentMon.getName(), 17, 3, p1.currentMon.getColor());
	Game::shared_instance().buffer.WriteBuffer("Health: " + to_string(p1.currentMon.getHealthCurrent()) + "/" + to_string(p1.currentMon.getHealthTotal()), 0, 4);

	Game::shared_instance().buffer.WriteBuffer("Player 2:", 0, 6);
	for (int i = 0; i < 6; i++) {
		if (p1.mon[i].alive == true) {
			Game::shared_instance().buffer.WriteBuffer("o", 10 + i * 2, 6, p1.mon[i].getColor());
		} else {
			Game::shared_instance().buffer.WriteBuffer(".", 10 + i * 2, 6, p1.mon[i].getColor());
		}
	}
	Game::shared_instance().buffer.WriteBuffer("Current Monster:", 0, 7);
	Game::shared_instance().buffer.WriteBuffer(p1.currentMon.getName(), 17, 7, p1.currentMon.getColor());
	Game::shared_instance().buffer.WriteBuffer("Health: " + to_string(p1.currentMon.getHealthCurrent()) + "/" + to_string(p1.currentMon.getHealthTotal()), 0, 8);
}

void BattleScene::showPlayerMoves(vector<Move> ms) {
	changeTextColorMove(m1);
	cout << "\n\n"
		<< m1.getName()
		<< "\nPower: " << m1.getPower()
		<< "\nAccuracy: " << m1.getAccuracy() << '\n';
	if (m1.getCooldown() > 1)
		cout << m1.getCooldown() << " Turn Cooldown";
	else if (m1.getCooldown() == 1)
		cout << "No Cooldown";
	else
		cout << "Passive Ability";
	changeTextColorDef();
}

int BattleScene::damageCalculator(bool player1Turn, Monster attacker, Monster defender, Move attack) {
	//damage checks

	//effect application
	if (attack.getEffect() == "Destroy Armor") {
		if (player1Turn)
			party2.currentMon.setDefenceCurrent(party2.currentMon.getdefenceCurrent() * 0.7);
		else
			party1.currentMon.setDefenceCurrent(party1.currentMon.getdefenceCurrent() * 0.7);

		cout << attacker.getName() << " has broken " << defender.getName() << "'s armor!\n";

	}
	if (attack.getEffect() == "Gain Armor") {
		if (player1Turn)
			party1.currentMon.setDefenceCurrent(party1.currentMon.getdefenceCurrent() * 1.2);
		else
			party2.currentMon.setDefenceCurrent(party2.currentMon.getdefenceCurrent() * 1.2);

		cout << attacker.getName() << " has built up its armor!\n";
	}

	if (attack.getEffect() == "Self Sacrifice") {
		if (player1Turn) {
			party1.currentMon.setHealthCurrent(party1.currentMon.getHealthCurrent() / 1.5);
			party1.currentMon.setAttackCurrent(party1.currentMon.getAttackCurrent() * 2);
		} else {
			party2.currentMon.setHealthCurrent(party2.currentMon.getHealthCurrent() / 1.5);
			party2.currentMon.setAttackCurrent(party2.currentMon.getAttackCurrent() * 2);
		}
		cout << attacker.getName() << " has drained it's own life!\n";
	}

	if (attack.getEffect() == "Heal") {
		if (player1Turn) {
			party1.currentMon.setHealthCurrent(party1.currentMon.getHealthCurrent() + party1.currentMon.getHealthTotal() / 2.7);
		} else {
			party2.currentMon.setHealthCurrent(party2.currentMon.getHealthCurrent() + party1.currentMon.getHealthTotal() / 2.7);
		}
		cout << attacker.getName() << " has regenerated it's health!\n";
	}


	bool accuracycheck = false;
	int damageAdvantage = 0.f;
	if (rand() % 100 <= attack.getAccuracy()) {
		accuracycheck = true;
		if (defender.getType() == "Grass" && attack.getType() == "Fire" || defender.getType() == "Fire" && attack.getType() == "Water" || defender.getType() == "Water" && attack.getType() == "Grass") {
			damageAdvantage += 2.0f;
			cout << "SUPER EFFECTIVE HIT!";
		} else if (defender.getType() == "Grass" && attack.getType() == "Water" || defender.getType() == "Fire" && attack.getType() == "Grass" || defender.getType() == "Water" && attack.getType() == "Fire") {
			damageAdvantage += 1.0f;
			cout << "WEAK HIT!";
		} else {
			damageAdvantage += 1.5f;
			cout << "HIT!";
		}
	} else
		cout << "MISS!";
	int temp = defender.getHealthCurrent();
	if (accuracycheck) {
		temp -= (((1.2 * attacker.getAttackCurrent() / defender.getdefenceCurrent()) * attack.getPower()) * damageAdvantage);
		cout << ' ' << (int)(((1.2 * attacker.getAttackCurrent() / defender.getdefenceCurrent()) * attack.getPower()) * damageAdvantage) << " DAMAGE DEALT!";
	}
	return temp;
}

int BattleScene::playerTurn(bool player1Turn, Monster p1, Monster p2) {
	bool madeSelection = false;
	int selection;

	if (player1Turn) {
		Game::shared_instance().buffer.WriteBuffer("Player 1 Turn!", 0, 0);
		if (p1.getMove1().getCooldownCurrent() > 1) {
			party1.currentMon.getMove1().setCooldownCurrent(p1.getMove1().getCooldownCurrent() - 1);
		}
		if (p1.getMove2().getCooldownCurrent() > 1) {
			party1.currentMon.getMove2().setCooldownCurrent(p1.getMove2().getCooldownCurrent() - 1);
		}
		if (p1.getMove3().getCooldownCurrent() > 1) {
			party1.currentMon.getMove3().setCooldownCurrent(p1.getMove3().getCooldownCurrent() - 1);
		}
		if (p1.getMove4().getCooldownCurrent() > 1) {
			party1.currentMon.getMove4().setCooldownCurrent(p1.getMove4().getCooldownCurrent() - 1);
		}
	} 
	else {
		Game::shared_instance().buffer.WriteBuffer("Player 2 Turn!", 0, 0);
		if (p2.getMove1().getCooldownCurrent() > 1) {
			party2.currentMon.getMove1().setCooldownCurrent(p2.getMove1().getCooldownCurrent() - 1);
		}
		if (p2.getMove2().getCooldownCurrent() > 1) {
			party2.currentMon.getMove2().setCooldownCurrent(p2.getMove2().getCooldownCurrent() - 1);
		}
		if (p2.getMove3().getCooldownCurrent() > 1) {
			party2.currentMon.getMove3().setCooldownCurrent(p2.getMove3().getCooldownCurrent() - 1);
		}
		if (p2.getMove4().getCooldownCurrent() > 1) {
			party2.currentMon.getMove4().setCooldownCurrent(p2.getMove4().getCooldownCurrent() - 1);
		}
	}

	drawCurrentHealth(party1, party2);

	showPlayerMoves(p1.getMoves());

	Game::shared_instance().buffer.WriteBuffer("Select move: ", 0, 2);
	cin >> selection;

	switch (selection) {
	case 1:
		if (p1.getMove1().getCooldownCurrent() == 1) {
			madeSelection = true;
			party1.currentMon.getMove1().setCooldownCurrent(p1.getMove1().getCooldown());
			p2.setHealthCurrent(damageCalculator(player1Turn, p1, p2, p1.getMove1()));
		}
		break;
	case 2:
		if (p1.getMove2().getCooldownCurrent() == 1) {
			madeSelection = true;
			party1.currentMon.getMove2().setCooldownCurrent(p1.getMove2().getCooldown());
			p2.setHealthCurrent(damageCalculator(player1Turn, p1, p2, p1.getMove2()));
		}
		break;
	case 3:
		if (p1.getMove3().getCooldownCurrent() == 1) {
			madeSelection = true;
			party1.currentMon.getMove3().setCooldownCurrent(p1.getMove3().getCooldown());
			p2.setHealthCurrent(damageCalculator(player1Turn, p1, p2, p1.getMove3()));
		}
		break;
	case 4:
		if (p1.getMove4().getCooldownCurrent() == 1) {
			madeSelection = true;
			party1.currentMon.getMove4().setCooldownCurrent(p1.getMove1().getCooldown());
			p2.setHealthCurrent(damageCalculator(player1Turn, p1, p2, p1.getMove4()));
		}
		break;
	default:
		break;
	}

	return p2.getHealthCurrent();
}
