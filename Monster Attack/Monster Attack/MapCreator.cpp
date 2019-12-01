#include "MapCreator.h"
#include "MapCreatorCursor.h"

void MapCreator::InitScene() {
	cout << "map width: ";
	cin >> map[0];
	cout << "map height: ";
	cin >> map[1];

	map[0] *= 2;
	mapSize = map[0] * map[1];

	//create map border
	string borderVert = "|" + string(map[0] + 2, ' ') + "|\n";
	mapBorder = string(map[0] + 4, '-') + "\n";

	for (size_t i = 0; i < map[1]; i++)
		mapBorder += borderVert;

	mapBorder += string(map[0] + 4, '-');

	entities.push_back(new MapCreatorCursor("@@", "cursor", map[0] / 2, map[1], 0));

	//init and populate the map background
	writeScreen.assign(mapSize, ' ');
	colorScreen.assign(mapSize, BACKGROUND_GREEN);

	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { map[0] + 4, map[1] + 2 });
}

void MapCreator::UpdateScene() {
	if (Input::GetKeyDown(VK_ESCAPE)) {
		Game::shared_instance().SwitchToScene(1);
		return;
	}

	Game::shared_instance().buffer.WriteBuffer(mapBorder, 0, 0, 6);
	Game::shared_instance().buffer.DisplayBackground(writeScreen, colorScreen, { {2, 1},  {map[0], map[1]} });

	for (Entity* currentEnt : entities)
		currentEnt->Update();

	if (Input::GetKeyDown('S'))
		Save("saveFile", map, writeScreen, colorScreen);

	if (Input::GetKeyDown('D'))
		Load("saveFile");
}

void MapCreator::UpdateSwitch() {
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { map[0] + 4, map[1] + 2 });
}

void MapCreator::Save(string fileName, vector<int> sizeMap, vector<char> writeMap, vector<int> colorMap) {
	ofstream theFile;

	theFile.open("assets/maps/" + fileName);

	if (!theFile.is_open())
		return;

	string writeMapStr{ "" };
	string colorMapStr{ "" };

	for (char curChar : writeMap)
		writeMapStr += curChar;

	for (int curInt : colorMap)
		colorMapStr += to_string(curInt) + " ";

	theFile << sizeMap[0] << "\n" << sizeMap[1] << "\n" << writeMapStr << "\n" << colorMapStr;

	theFile.close();
}

void MapCreator::Load(string fileName) {
	ifstream theFile;

	theFile.open("assets/maps/" + fileName);

	if (!theFile.is_open())
		return;

	string inp;
	writeScreen.clear();
	colorScreen.clear();

	getline(theFile, inp);
	map[0] = atoi(inp.c_str());

	getline(theFile, inp);
	map[1] = atoi(inp.c_str());

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

	entities.clear();
	entities.push_back(new MapCreatorCursor("@@", "cursor", map[0] / 2, map[1], 0));

	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { map[0] + 4, map[1] + 2 });
}
