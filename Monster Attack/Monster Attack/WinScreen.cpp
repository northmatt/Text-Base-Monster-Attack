#include "WinScreen.h"

void WinScreen::InitScene() {
	LoadIntoString("youWin.txt", title);
	centerOfScreen = Game::shared_instance().buffer.GetCSBI().dwSize.X / 4.f;
}

void WinScreen::UpdateScene() {
	Game::shared_instance().buffer.WriteBuffer(title, centerOfScreen - 31.5, 1);

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
			Game::shared_instance().SwitchToScene(0);
			return;
		case 1:
			Game::shared_instance().SwitchToScene(4, false, true);
			return;
		case 2:
			Game::shared_instance().isRunning = false;
			return;
		default:
			break;
		}
	}

	Game::shared_instance().buffer.WriteBuffer(string(24, ' '), centerOfScreen - 6, 30 + selection * 2, 6);

	Game::shared_instance().buffer.WriteBuffer("Titlescreen", centerOfScreen - 3.25, 30, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Restart", centerOfScreen - 1.75, 32, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Quit Game", centerOfScreen - 2.25, 34, FOREGROUND_INTENSITY, true);
}

void WinScreen::UpdateSwitch() {
	Game::shared_instance().PlayMusic("11-fanfare");
	selection = 0;
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { 1, 1 });
	Game::shared_instance().buffer.SetCamPos({1, 1});
}

void WinScreen::LoadIntoString(string fileName, string& stringToEdit) {
	ifstream theFile;

	theFile.open("assets/text/" + fileName);

	if (!theFile.is_open())
		return;

	string inp;

	while(getline(theFile, inp))
		stringToEdit += inp + "\n";

	theFile.close();
}
