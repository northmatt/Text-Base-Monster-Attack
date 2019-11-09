#include "Game.h"

void Game::InitGame() {
	cout << "Game Init\n";

	hConsole = GetStdHandle(STD_INPUT_HANDLE);
	loadedScenes.push_back(new BattleScene());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	FpsCap();

	currentScene->UpdateScene();

	return (!inp.GetKeyDown('Q'));
}

void Game::FpsCap() {
	a = system_clock::now();
	duration<double, milli> work_time = a - b;

	if (work_time.count() < timeWait) {
		duration<double, std::milli> delta_ms(timeWait - work_time.count());
		milliseconds delta_ms_duration = duration_cast<milliseconds>(delta_ms);
		sleep_for(milliseconds(delta_ms_duration.count()));
	}

	b = system_clock::now();
	duration<double, milli> sleep_time = b - a;
}

/*
   38
37 40 39
*/