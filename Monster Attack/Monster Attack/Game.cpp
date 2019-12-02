#include "Game.h"
#include "Titlescreen.h"
#include "Pausescreen.h"
#include "MultiplayerWin.h"
#include "MapCreator.h"
#include "BattleScene.h"
#include "MapLevel.h"
#include "BattleSceneAI.h"
#include "LoseScreen.h"
#include "WinScreen.h"
#include "IntroScreen.h"

void Game::InitGame() {
	srand(time(0));

	//loads the scenes into memory
	loadedScenes.push_back(new Titlescreen());
	loadedScenes.push_back(new Pausescreen());
	loadedScenes.push_back(new MapCreator());
	loadedScenes.push_back(new BattleScene());
	loadedScenes.push_back(new MapLevel());
	loadedScenes.push_back(new BattleSceneAI());
	loadedScenes.push_back(new MultiplayerWin());
	loadedScenes.push_back(new LoseScreen());
	loadedScenes.push_back(new WinScreen());
	loadedScenes.push_back(new IntroScreen());

	currentScene = loadedScenes[0];
}

bool Game::UpdateGame() {
	//cap FPS
	Time::FpsCap();

	Input::updateInps();

	isRunning = !Input::GetKeyDown(VK_F4);

	currentScene->UpdateScene();

	buffer.DisplayBuffer();

	if (switchingToScene > 0)
		internalSwitchScene();

	return isRunning;
}

void Game::SwitchToScene(int index, bool addFromCurrentScene, bool resetScene) {
	lastSceneIndex = currentSceneIndex;

	if (addFromCurrentScene) {
		currentSceneIndex += index;
		int indSize = static_cast<int>(loadedScenes.size());

		if (currentSceneIndex < 0)
			currentSceneIndex += indSize;
		else if (currentSceneIndex >= indSize)
			currentSceneIndex -= indSize;
	} else
		currentSceneIndex = index;

	if (resetScene)
		switchingToScene = 2;
	else
		switchingToScene = 1;
}

void Game::PlayMusic(string songName, bool stopOld) {
	if (stopOld)
		mciSendString(L"close mp3", NULL, 0, NULL);
	
	string testStuff = "open \"assets/sounds/" + songName + ".mp3\" type mpegvideo alias mp3";
	wchar_t* wide_string = new wchar_t[testStuff.length() + 1];
	std::copy(testStuff.begin(), testStuff.end(), wide_string);
	wide_string[testStuff.length()] = 0;

	mciSendString(wide_string, NULL, 0, NULL);
	mciSendString(L"play mp3", NULL, 0, NULL);
	mciSendString(L"play mp3 repeat", NULL, 0, NULL);

	delete[] wide_string;
}

void Game::internalSwitchScene() {
	currentScene->BeforeUpdateSwitch();

	currentScene = loadedScenes[currentSceneIndex];
	currentScene->UpdateSwitch();

	if (switchingToScene == 2)
		currentScene->InitScene();

	switchingToScene = 0;
}

/*
static Game *instance() {if (!_inst) _inst = new Game(); return _inst;}
static S& instance() { static S inst; return inst; }
   38
37 40 39
*/