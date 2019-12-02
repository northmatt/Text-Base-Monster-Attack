#pragma once

#include "Game.h"

using std::round;

class TextBox : public Entity {
public:
	TextBox(string _text, int _color, double _killTime, double _posX, double _posY);

	void Update(size_t _index) override;
private:
	double killTime{ 1 };
};