#include "main.h"

int main() {
	Game::shared_instance().InitGame();

	bool isRunning = true;
	while (isRunning)
		isRunning = Game::shared_instance().UpdateGame();

	return 0;
}