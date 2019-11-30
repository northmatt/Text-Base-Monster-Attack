#include "Titlescreen.h"

void Titlescreen::InitScene() {
	LoadIntoString("titlescreen.txt", title);
	centerOfScreen = Game::shared_instance().buffer.GetCSBI().dwSize.X / 4.f;
}

void Titlescreen::UpdateScene() {
	Game::shared_instance().buffer.WriteBuffer(title, centerOfScreen - 46, 1);

	if (Input::GetKeyDown(38)) {
		selection--;

		if (selection < 0)
			selection = 2;
	}

	if (Input::GetKeyDown(40)) {
		selection++;

		if (selection > 2)
			selection = 0;
	}

	if (Input::GetKeyDown(VK_RETURN)) {
		switch (selection) {
		case 0:
			Game::shared_instance().SwitchToScene(3, false, true);
			return;
		case 1:
			Game::shared_instance().SwitchToScene(2, false, true);
			return;
		case 2:
			Game::shared_instance().isRunning = false;
			return;
		default:
			break;
		}
	}

	Game::shared_instance().buffer.WriteBuffer(string(24, ' '), centerOfScreen - 6, 30 + selection * 2, 6);

	Game::shared_instance().buffer.WriteBuffer("Start Singleplayer Game", centerOfScreen - 6, 30, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Start Multiplayer Game", centerOfScreen - 5.75, 32, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Quit Game", centerOfScreen - 2.25, 34, FOREGROUND_INTENSITY, true);
}

void Titlescreen::UpdateSwitch() {
	selection = 0;
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { 1, 1 });
	Game::shared_instance().buffer.SetCamPos({1, 1});
}

void Titlescreen::LoadIntoString(string fileName, string& stringToEdit) {
	ifstream theFile;

	theFile.open("assets/text/" + fileName);

	if (!theFile.is_open())
		return;

	string inp;

	while(getline(theFile, inp))
		stringToEdit += inp + "\n";

	theFile.close();
}
