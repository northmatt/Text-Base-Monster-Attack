#pragma once

#include <vector>
#include "Move.h"

using std::vector;

class Monster {
private:
	string name, type, lightType;
	int healthTotal, attackTotal, defenceTotal, speedTotal, color, passiveReset;
	int healthCurrent, attackCurrent, defenceCurrent, speedCurrent;
	Move move1, move2, move3, move4, movePassive;
public:
	bool alive = true;
	//set
	void setName(string a) { name = a; }
	void setType(string a) { type = a; }
	void setLightType(string a) { lightType = a; }
	void setHealthTotal(int a) { healthTotal = a; }
	void setHealthCurrent(int a) { healthCurrent = a; }
	void setAttackTotal(int a) { attackTotal = a; }
	void setAttackCurrent(int a) { attackCurrent = a; }
	void setDefenceTotal(int a) { defenceTotal = a; }
	void setDefenceCurrent(int a) { defenceCurrent = a; }
	void setSpeedTotal(int a) { speedTotal = a; }
	void setSpeedCurrent(int a) { speedCurrent = a; }
	void setColor(int col) { color = col; }
	void setPassiveReset(int pass) { passiveReset = pass; }
	void setMove1(Move a) { move1 = a; }
	void setMove2(Move a) { move2 = a; }
	void setMove3(Move a) { move3 = a; }
	void setMove4(Move a) { move4 = a; }
	void setMovePassive(Move a) { movePassive = a; }
	//get
	string getName() { return name; }
	string getType() { return type; }
	string getLightType() { return lightType; }
	int getHealthTotal() { return healthTotal; }
	int getHealthCurrent() { return healthCurrent; }
	int getAttackTotal() { return attackTotal; }
	int getAttackCurrent() { return attackCurrent; }
	int getDefenceTotal() { return defenceTotal; }
	int getdefenceCurrent() { return defenceCurrent; }
	int getSpeedTotal() { return speedTotal; }
	int getSpeedCurrent() { return speedCurrent; }
	vector<Move> getMoves() { return {move1, move2, move3, move4}; }
	int getColor() { return color; }
	int getPassiveReset() { return passiveReset; }
	Move* getMove1() { return &move1; }
	Move* getMove2() { return &move2; }
	Move* getMove3() { return &move3; }
	Move* getMove4() { return &move4; }
	Move getMovePassive() { return movePassive; }
	//constructor
	Monster() {
		name = "NULL"; type = "NULL"; lightType = "NULL"; attackCurrent = 0; attackTotal = 0;
		healthCurrent = 0; healthTotal = 0; defenceCurrent = 0; defenceTotal = 0;
		speedCurrent = 0; speedTotal = 0; color = 0;
	}
	Monster(string _name, string _type, string _lType, int health, int attack, int defence, int speed, int col, Move m1, Move m2, Move m3, Move m4) {
		setName(_name); setType(_type); setLightType(_lType);
		setHealthTotal((health * 4) + 220); setHealthCurrent(getHealthTotal());
		setAttackTotal((attack * 2.2) + 10); setAttackCurrent(getAttackTotal());
		setDefenceTotal((defence * 2) + 5); setDefenceCurrent(getDefenceTotal());
		setSpeedTotal((speed) * 2.3 + 10); setSpeedCurrent(getSpeedTotal());
		setColor(col);
		setMove1(m1); setMove2(m2); setMove3(m3); setMove4(m4);
	}
};