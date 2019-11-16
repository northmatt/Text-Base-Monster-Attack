#include "MapCreator.h"
#include "MapCreatorCursor.h"

void MapCreator::InitScene() {
	cout << "map width: ";
	cin >> mapWidth;
	cout << "map height: ";
	cin >> mapHeight;

	string borderVert = "|" + string(mapWidth * 2 + 2, ' ') + "|\n";
	mapBorder = string(mapWidth * 2 + 4, '-') + "\n";

	for (size_t i = 0; i < mapHeight; i++)
		mapBorder += borderVert;

	mapBorder += string(mapWidth * 2 + 4, '-');

	entities.push_back(new MapCreatorCursor("  ", "cursor", mapWidth, mapHeight));
	mapSize = mapHeight * mapWidth;
	writeScreen = new (nothrow) char[mapSize] { ' ' };
	colorScreen = new (nothrow) int[mapSize] { 7 };
}

void MapCreator::UpdateScene() {
	Game::shared_instance().buffer.WriteBuffer(mapBorder, 0, 0, 6);

	for (Entity* currentEnt : entities)
		currentEnt->Update();

	//do camera code
}
