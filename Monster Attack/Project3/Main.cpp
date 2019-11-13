#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

#include "Move.h"
#include "Monster.h"

using namespace std;

struct Party
{
	Monster mon[6];
	Monster currentMon;
	int currentMonSlot = 1;
};

void drawCurrentHealth(Party p1, Party p2) {
	cout << "\x1B[2J\x1B[H";
	cout << "Player 1:\t\t";
	for (int i = 0; i < 6; i++) {
		if (p1.mon[i].alive == true)
			cout << "o ";
		else
			cout << ". ";
	}
	cout << "\nCurrent Monster:\t" << p1.currentMon.getName()
		<< "\nHealth:\t\t\t" << p1.currentMon.getHealthCurrent() << "/" << p1.currentMon.getHealthTotal();
	cout << "\n\nPlayer 2:\t\t";
	for (int i = 0; i < 6; i++) {
		if (p2.mon[i].alive == true)
			cout << "o ";
		else
			cout << ". ";
	}
	cout << "\nCurrent Monster:\t" << p2.currentMon.getName()
		<< "\nHealth:\t\t\t" << p2.currentMon.getHealthCurrent() << "/" << p2.currentMon.getHealthTotal();
}

void showPlayerMoves(Move m1) {
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
}

int damageCalculator(Monster attacker, Monster defender, Move attack){
	bool accuracycheck = false;
	int damageAdvantage = 1.5f;
	if (rand() % 100 <= attack.getAccuracy()) {
		accuracycheck = true;
		if (defender.getType() == "Grass" && attack.getType() == "Fire" || defender.getType() == "Fire" && attack.getType() == "Water" || defender.getType() == "Water" && attack.getType() == "Earth") {
			damageAdvantage = 2.0f;
			cout << "SUPER EFFECTIVE HIT!";
		}
		else if (defender.getType() == "Grass" && attack.getType() == "Water" || defender.getType() == "Fire" && attack.getType() == "Grass" || defender.getType() == "Water" && attack.getType() == "Fire") {
			damageAdvantage = 1.0f;
			cout << "WEAK HIT!";
		}
		else {
			cout << "HIT!";
		}
	}
	else
		cout << "MISS!";
	int temp = defender.getHealthCurrent();
	if (accuracycheck) {
		temp -= (((1.2 * attacker.getAttackCurrent() / defender.getdefenceCurrent()) * attack.getPower())*damageAdvantage);
	}
	return temp;
}

Monster playerTurn(Monster p1, Monster p2) {
	
	int selection;


	showPlayerMoves(p1.getMove1());
	showPlayerMoves(p1.getMove2());
	showPlayerMoves(p1.getMove3());
	showPlayerMoves(p1.getMove4());

	cout << "\n\nSelect move: ";
	cin >> selection;

	if (selection == 1) {
		p2.setHealthCurrent(damageCalculator(p1, p2, p1.getMove1()));
	}
	else if (selection == 2) {
		p2.setHealthCurrent(damageCalculator(p1, p2, p1.getMove2()));
	}
	else if (selection == 3) {
		p2.setHealthCurrent(damageCalculator(p1, p2, p1.getMove3()));
	}
	else if (selection == 4) {
		p2.setHealthCurrent(damageCalculator(p1, p2, p1.getMove4()));
	}

	return p2;
}

int main() {
	srand(time(NULL));
	//init
	Move fire_punch("Fire Punch", "None", "Fire", 20, 100, 1);
	Move grass_punch("Grass Punch", "None", "Grass", 20, 100, 1);
	Move flame_nova("Flame Nova", "None", "Fire", 50, 85, 2);
	Move grass_nova("Grass Nova", "None", "Grass", 50, 85, 2);
	Move flame_blast("Flame Blast", "None", "Fire", 80, 85, 3);
	Move earth_blast("Earth Blast", "None", "Grass", 80, 85, 3);
	Move volcanic_eruption("Volcanic Eruption", "None", "Fire", 200, 50, 8);
	Move sinkhole("Sinkhole", "None", "Grass", 200, 50, 8);
	Monster chickora("Chickora", "Fire", 500, 30, 20, 20, fire_punch, flame_nova, flame_blast, volcanic_eruption);
	Monster hamion("Hamion", "Grass", 500, 30, 20, 20, grass_punch, grass_nova, earth_blast, sinkhole);
	Monster chickora2("Chickora 1", "Fire", 500, 30, 20, 20, fire_punch, flame_nova, flame_blast, volcanic_eruption);
	Monster hamion2("Hamion 1", "Grass", 500, 30, 20, 20, grass_punch, grass_nova, earth_blast, sinkhole);
	Monster chickora3("Chickora 2", "Fire", 500, 30, 20, 20, fire_punch, flame_nova, flame_blast, volcanic_eruption);
	Monster hamion3("Hamion 2", "Grass", 500, 30, 20, 20, grass_punch, grass_nova, earth_blast, sinkhole);

	Party party1, party2;

	party1.mon[0] = chickora;
	party1.mon[1] = hamion;
	party1.mon[2] = chickora2;
	party1.mon[3] = hamion2;
	party1.mon[4] = chickora3;
	party1.mon[5] = hamion3;
	party1.currentMon = party1.mon[0];
	party1.currentMonSlot = 0;

	party2.mon[0] = hamion;
	party2.mon[1] = chickora;
	party2.mon[2] = hamion2;
	party2.mon[3] = chickora2;
	party2.mon[4] = hamion3;
	party2.mon[5] = chickora3;
	party2.currentMon = party2.mon[0];
	party2.currentMonSlot = 0;

	while (1) {
		drawCurrentHealth(party1, party2);
		cout << "\n\nPlayer 1 Turn!";
		party2.currentMon = playerTurn(party1.currentMon, party2.currentMon);
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
		Sleep(1000);
		drawCurrentHealth(party1, party2);
		cout << "\n\nPlayer 2 Turn!";
		party1.currentMon = playerTurn(party2.currentMon, party1.currentMon);
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
		Sleep(1000);
	}
}