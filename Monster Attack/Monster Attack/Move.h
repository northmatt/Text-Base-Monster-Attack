#pragma once
#include <iostream>
#include <string>

using std::string;

class Move {
private:
	string name, effect, type;
	int power, accuracy, cooldown, cooldownCurrent, color;
public:
	//set
	void setName(string a) { name = a; }
	void setEffect(string a) { effect = a; }
	void setType(string a) { type = a; }
	void setPower(int a) { power = a; }
	void setAccuracy(int a) { accuracy = a; }
	void setCooldown(int a) { cooldown = a; }
	void setCooldownCurrent(int a) { cooldownCurrent = a; }
	void setColor(int col) { color = col; }
	//get
	string getName() { return name; }
	string getEffect() { return effect; }
	string getType() { return type; }
	int getPower() { return power; }
	int getAccuracy() { return accuracy; }
	int getCooldown() { return cooldown; }
	int getCooldownCurrent() { return cooldownCurrent; }
	int getColor() { return color; }
	//constructor
	Move() { name = "NULL", effect = "NULL", type = "NULL", power = 0; accuracy = 0; cooldown = 0; color = 0; }
	Move(string _name, string _effect, string _type, int _power, int _accuracy, int _cooldown, int _color) {
		setName(_name); setEffect(_effect); setType(_type); setPower(_power); setAccuracy(_accuracy); setCooldown(_cooldown);
		setCooldownCurrent(1); setColor(_color);
	}
};