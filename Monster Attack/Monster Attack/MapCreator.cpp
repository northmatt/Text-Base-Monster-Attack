#include "MapCreator.h"
#include "MapCreatorCursor.h"

#include <random>
#include <time.h>
using std::rand;

void MapCreator::InitScene() {
	map.resize(2);
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

	entities.push_back(new MapCreatorCursor("@@", "cursor", map[0] / 2, map[1], 20));

	//init and populate the map background
	writeScreen.assign(mapSize, ' ');
	colorScreen.assign(mapSize, BACKGROUND_GREEN);

	srand(time(0));
	int numOfLakes = rand() % 10 + 3;

	for (int i = 0; i < colorScreen.size() ; i += 2) {
		if (rand() % 10 >= 9) {
			colorScreen[i] = BACKGROUND_BLUE;
			colorScreen[i + 1] = BACKGROUND_BLUE;
		}
	}

	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, {map[0] + 4, map[1] + 2});
}

void MapCreator::UpdateScene() {
	Game::shared_instance().buffer.WriteBuffer(mapBorder, 0, 0, 6);
	Game::shared_instance().buffer.DisplayBackground(writeScreen, colorScreen, { {2, 1},  {map[0], map[1]} });

	for (Entity* currentEnt : entities)
		currentEnt->Update();
}

void MapCreator::UpdateSwitch() {
	Game::shared_instance().buffer.SetMaxCam({ 0, 0 }, { map[0] + 4, map[1] + 2 });
}
