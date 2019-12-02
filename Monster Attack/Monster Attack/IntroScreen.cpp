#include "IntroScreen.h"

void IntroScreen::InitScene() {
	LoadIntoString("Intro.txt", title);
	LoadIntoString("IntroText.txt", bodyText);
	centerOfScreen = Game::shared_instance().buffer.GetCSBI().dwSize.X / 4.f;
}

void IntroScreen::UpdateScene() {
	Game::shared_instance().buffer.WriteBuffer(title, centerOfScreen - 21.5, 1);
	Game::shared_instance().buffer.WriteBuffer(bodyText, 1, 20);

	if (Input::GetKeyDown(38)) {
		selection--;

		if (selection < 0)
			selection = 1;
	}

	if (Input::GetKeyDown(40)) {
		selection++;

		if (selection > 1)
			selection = 0;
	}

	if (Input::GetKeyDown(VK_RETURN)) {
		switch (selection) {
		case 0:
			Game::shared_instance().SwitchToScene(4, false, true);
			return;
		case 1:
			Game::shared_instance().SwitchToScene(0);
			return;
		default:
			break;
		}
	}

	Game::shared_instance().buffer.WriteBuffer(string(24, ' '), centerOfScreen - 6, 40 + selection * 2, 6);

	Game::shared_instance().buffer.WriteBuffer("Start", centerOfScreen - 1.25, 40, FOREGROUND_INTENSITY, true);
	Game::shared_instance().buffer.WriteBuffer("Titlescreen", centerOfScreen - 2.75, 42, FOREGROUND_INTENSITY, true);
}

void IntroScreen::UpdateSwitch() {
	Game::shared_instance().PlayMusic("03-mako-reactor");
	selection = 0;
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { 1, 1 });
	Game::shared_instance().buffer.SetCamPos({1, 1});
}

void IntroScreen::LoadIntoString(string fileName, string& stringToEdit) {
	ifstream theFile;

	theFile.open("assets/text/" + fileName);

	if (!theFile.is_open())
		return;

	string inp;

	while(getline(theFile, inp))
		stringToEdit += inp + "\n";

	theFile.close();
}
