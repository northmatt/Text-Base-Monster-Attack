#include "main.h"

int main() {
	Game theGame;

	theGame.InitGame();

	bool isRunning = true;
	while (isRunning)
		isRunning = theGame.UpdateGame();
}