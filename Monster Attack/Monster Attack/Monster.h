#pragma once

#include <vector>
#include "Move.h"

using std::vector;

class Monster {
private:
	string name, type, lightType;
	int healthTotal, attackTotal, defenceTotal, speedTotal, color, passiveReset;
	int healthCurrent, attackCurrent, defenceCurrent, speedCurrent;
	float attackTemp, defenceTemp, speedTemp;
	Move move1, move2, move3, move4, movePassive;
	vector<Move> currentEffects;
public:
	bool alive = false;
	//resetTempMods
	void ResetTemp() { attackTemp = 1.f; defenceTemp = 1.f; speedTemp = 1.f; };
	//set
	void setName(string a) { name = a; }
	void setType(string a) { type = a; }
	void setLightType(string a) { lightType = a; }
	void setHealthTotal(int a) { healthTotal = a; }
	void setHealthCurrent(int a) { healthCurrent = a; }
	void addHealth(int a) { healthCurrent = min(healthTotal, healthCurrent + a); }
	void setAttackTotal(int a) { attackTotal = a; }
	void setAttackCurrent(int a) { attackCurrent = a; }
	void setDefenceTotal(int a) { defenceTotal = a; }
	void setDefenceCurrent(int a) { defenceCurrent = a; }
	void setSpeedTotal(int a) { speedTotal = a; }
	void setSpeedCurrent(int a) { speedCurrent = a; }
	void setColor(int col) { color = col; }
	void setMove1(Move a) { move1 = a; }
	void setMove2(Move a) { move2 = a; }
	void setMove3(Move a) { move3 = a; }
	void setMove4(Move a) { move4 = a; }
	void setMovePassive(Move a) { movePassive = a; }
	void setAttackTemp(float a) { attackTemp = a; }
	void setDefenceTemp(float a) { defenceTemp = a; }
	void setSpeedTemp(float a) { speedTemp = a; }
	void addAttackTemp(float a) { attackTemp += a; }
	void addDefenceTemp(float a) { defenceTemp += a; }
	void addSpeedTemp(float a) { speedTemp += a; }
	void addEffect(Move a) {
		for (Move curMov : currentEffects)
			if (curMov.getEffect() == a.getEffect())
				return;

		currentEffects.push_back(a);
	}
	void removeEffect(size_t i) { currentEffects.erase(currentEffects.begin() + i); }
	void resetAll() {
		ResetTemp();
		setHealthCurrent(getHealthTotal());
		setAttackCurrent(getAttackTotal());
		setDefenceCurrent(getDefenceTotal());
		setSpeedCurrent(getSpeedTotal());
		alive = true;
	}
	//get
	string getName() { return name; }
	string getType() { return type; }
	string getLightType() { return lightType; }
	int getHealthTotal() { return healthTotal; }
	int getHealthCurrent() { return healthCurrent; }
	int getAttackTotal() { return attackTotal * attackTemp; }
	int getAttackCurrent() { return attackCurrent * attackTemp; }
	int getDefenceTotal() { return defenceTotal * defenceTemp; }
	int getdefenceCurrent() { return defenceCurrent * defenceTemp; }
	int getSpeedTotal() { return speedTotal * speedTemp; }
	int getSpeedCurrent() { return speedCurrent * speedTemp; }
	vector<Move> getMoves() { return {move1, move2, move3, move4, movePassive}; }
	int getColor() { return color; }
	Move* getMove1() { return &move1; }
	Move* getMove2() { return &move2; }
	Move* getMove3() { return &move3; }
	Move* getMove4() { return &move4; }
	Move* getMovePassive() { return &movePassive; }
	vector<Move>* getEffects() { return &currentEffects; }
	Move* getEffect(size_t i) { return &currentEffects[i]; }
	float getAttackTemp() { return attackTemp; }
	float getDefenceTemp() { return defenceTemp; }
	float getSpeedTemp() { return speedTemp; }
	//constructor
	Monster() {
		name = "NULL"; type = "NULL"; lightType = "NULL"; attackCurrent = 0; attackTotal = 0;
		healthCurrent = 0; healthTotal = 0; defenceCurrent = 0; defenceTotal = 0;
		speedCurrent = 0; speedTotal = 0; color = 0; ResetTemp();
	}
	Monster(string _name, string _type, string _lType, int health, int attack, int defence, int speed, int col, Move m1, Move m2, Move m3, Move m4, Move mp) {
		ResetTemp();
		setName(_name); setType(_type); setLightType(_lType);
		setHealthTotal((health * 4) + 220); setHealthCurrent(getHealthTotal());
		setAttackTotal((attack * 2.2) + 10); setAttackCurrent(getAttackTotal());
		setDefenceTotal((defence * 2) + 5); setDefenceCurrent(getDefenceTotal());
		setSpeedTotal((speed) * 2.3 + 10); setSpeedCurrent(getSpeedTotal());
		setColor(col);
		setMove1(m1); setMove2(m2); setMove3(m3); setMove4(m4); setMovePassive(mp);
		alive = true;
	}
};