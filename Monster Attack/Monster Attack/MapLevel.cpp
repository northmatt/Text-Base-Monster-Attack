#include "MapLevel.h"
#include "MapLevelCursor.h"

void MapLevel::InitScene() {
	Load("saveFile");
}

void MapLevel::UpdateScene() {
	if (Input::GetKeyDown(VK_ESCAPE)) {
		Game::shared_instance().SwitchToScene(1);
		return;
	}

	Game::shared_instance().buffer.WriteBuffer(mapBorder, 0, 0, 6);
	Game::shared_instance().buffer.DisplayBackground(writeScreen, colorScreen, { {2, 1},  {map[0], map[1]} });

	for (Entity* currentEnt : entities)
		currentEnt->Update();
}

void MapLevel::UpdateSwitch() {
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { map[0] + 4, map[1] + 2 });
	Game::shared_instance().buffer.SetCamPos({ 1, 1 });
}

void MapLevel::Load(string fileName) {
	ifstream theFile;

	theFile.open("assets/maps/" + fileName);

	if (!theFile.is_open())
		return;

	string inp;
	writeScreen.clear();
	colorScreen.clear();
	map.clear();
	entities.clear();

	getline(theFile, inp);
	map.push_back(atoi(inp.c_str()));

	getline(theFile, inp);
	map.push_back(atoi(inp.c_str()));

	mapSize = map[0] * map[1];

	getline(theFile, inp);
	for (char curChar : inp)
		if (curChar != '\n')
			writeScreen.push_back(curChar);

	getline(theFile, inp);

	string strBuffer;
	stringstream ss(inp);

	while (ss >> strBuffer)
		colorScreen.push_back(atoi(strBuffer.c_str()));

	theFile.close();

	//create map border
	string borderVert = "|" + string(map[0] + 2, ' ') + "|\n";
	mapBorder = string(map[0] + 4, '-') + "\n";

	for (size_t i = 0; i < map[1]; i++)
		mapBorder += borderVert;

	mapBorder += string(map[0] + 4, '-');

	entities.push_back(new MapLevelCursor("@@", "cursor", map[0] / 2, map[1]));
}
