#include "MapLevel.h"
#include "MapLevelCursor.h"

void MapLevel::InitScene() {
	Load("saveFile");
	Monsters mons;

	BattlePlayer* thePlayer = nullptr;
	thePlayer = new BattlePlayer;
	thePlayer->name = "Player 1";
	thePlayer->mon[0] = mons._1;
	thePlayer->currentMonSlot = 0;
	Game::shared_instance().SetMainPlayer(thePlayer);

	BattlePlayer* theEnemy = nullptr;
	theEnemy = new BattlePlayer;
	theEnemy->name = "Player 2";
	theEnemy->mon[0] = mons._2;
	theEnemy->currentMonSlot = 0;
	Game::shared_instance().SetMainEnemy(theEnemy);
}

void MapLevel::UpdateScene() {
	if (Input::GetKeyDown(VK_ESCAPE)) {
		Game::shared_instance().SwitchToScene(1);
		return;
	}

	if (Input::GetKeyDown(VK_F1)) {
		Game::shared_instance().SwitchToScene(5);
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
	entities.clear();

	getline(theFile, inp);
	map[0] = atoi(inp.c_str());

	getline(theFile, inp);
	map[1] = atoi(inp.c_str());

	mapSize = map[0] * map[1];
	entities.push_back(new MapLevelCursor("@@", "cursor", map[0] / 2, map[1]));
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { map[0] + 4, map[1] + 2 });

	getline(theFile, inp);
	for (size_t i = 0; i < mapSize; i++) {
		char curChar = inp[i];
		if (curChar == 'P') {
			//index = (pos.x - 1) + ( (pos.y - 1) * map[0] )
			//pos.y = index / map[0]
			//
			entities[0]->pos.y = i / map[0] + 1;
			entities[0]->pos.x = (i - (entities[0]->pos.y - 1) * map[0]) / 2;
			writeScreen.push_back(' ');
		} else if (curChar != '\n')
				writeScreen.push_back(curChar);
	}

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
}
