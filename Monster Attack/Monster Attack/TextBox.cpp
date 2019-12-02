#include "TextBox.h"

TextBox::TextBox(string _text, int _color, double _killTime, double _posX, double _posY) {
	string horzBorder(_text.length() + 4, '-');
	string vertBorder = "| " + string(_text.length(), ' ') + " |";
	//print the message while adding the box around around the text
	for (size_t i = 0; i < 5; i++) {
		if (i == 0 || i == 4)
			image += horzBorder;
		else if (i == 1 || i == 3)
			image += "\n" + vertBorder + "\n";
		else
			image += "| " + _text + " |";
	}

	killTime = _killTime;
	pos.x = _posX - horzBorder.size() / 4;
	pos.y = _posY - 2.5;
	color = _color;
}

void TextBox::Update(size_t _index) {
	killTime -= Time::deltaTime;
	if (killTime <= 0) {
		Game::shared_instance().GetCurrentScene()->removeEntity(_index);
	}

	Game::shared_instance().buffer.WriteBuffer(image, pos.x, pos.y, color, false, true);
}
