#include "Pausescreen.h"

void Pausescreen::InitScene() {
	LoadIntoString("pausescreen.txt", title);
	centerOfScreen = Game::shared_instance().buffer.GetCSBI().dwSize.X / 4.f;
}

void Pausescreen::UpdateScene() {
	Game::shared_instance().buffer.WriteBuffer(title, centerOfScreen - 23.5, 1);

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
			Game::shared_instance().SwitchToScene(Game::shared_instance().GetLastSceneIndex());
			return;
		case 1:
			Game::shared_instance().SwitchToScene(0);
			return;
		case 2:
			Game::shared_instance().isRunning = false;
			return;
		default:
			break;
		}
	}

	Game::shared_instance().buffer.WriteBuffer(string(24, ' '), centerOfScreen - 6, 30 + selection * 2, 6);

	Game::shared_instance().buffer.WriteBuffer("Return", centerOfScreen - 1.5, 30, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Main Menu", centerOfScreen - 2.25, 32, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Quit Game", centerOfScreen - 2.25, 34, FOREGROUND_INTENSITY, true);
}

void Pausescreen::UpdateSwitch() {
	Game::shared_instance().PlayMusic("21-the-north-cave");
	selection = 0;
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { 1, 1 });
	Game::shared_instance().buffer.SetCamPos({ 1, 1 });
}

void Pausescreen::LoadIntoString(string fileName, string& stringToEdit) {
	ifstream theFile;

	theFile.open("assets/text/" + fileName);

	if (!theFile.is_open())
		return;

	string inp;

	while (getline(theFile, inp))
		stringToEdit += inp + "\n";

	theFile.close();
}
