#include "MapCreator.h"
#include "MapCreatorCursor.h"

void MapCreator::InitScene() {
	map.resize(2);
	cout << "map width: ";
	cin >> map[0];
	cout << "map height: ";
	cin >> map[1];

	map[0] *= 2;

	string borderVert = "|" + string(map[0] + 2, ' ') + "|\n";
	mapBorder = string(map[0] + 4, '-') + "\n";

	for (size_t i = 0; i < map[1]; i++)
		mapBorder += borderVert;

	mapBorder += string(map[0] + 4, '-');

	entities.push_back(new MapCreatorCursor("  ", "cursor", map[0] / 2, map[1]));
	mapSize = map[0] * map[1];

	writeScreen.assign(mapSize, 'a');
	colorScreen.assign(mapSize, 5);

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
