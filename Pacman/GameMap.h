#pragma once
#include "Texture.h"
class Game;

enum MapCell {
	Empty,
	Wall,
	Food,
	Vitamins
};

class GameMap
{
private:
	Game* game = nullptr;
	Texture* wall = nullptr;
	Texture* food = nullptr;
	Texture * vitamin = nullptr;
	MapCell* map = nullptr;
	unsigned int rows;
	unsigned int cols;

public:
	GameMap();
	GameMap(unsigned int rows, unsigned int cols, Texture* wall, Texture* food, Texture * vitamin, Game * game);
	~GameMap();
	const MapCell getCellType(unsigned int row, unsigned int col) const;
	void setCellType(unsigned int row, unsigned int col, MapCell type);
	void render();
	void update();

	const unsigned int getRows() const;
	const unsigned int getCols() const;
};

