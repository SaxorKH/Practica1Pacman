#pragma once
#include "PacManObject.h"
#include "Texture.h"
class Game;

enum MapCell {
	Empty,
	Wall,
	Food,
	Vitamins
};

class GameMap : public PacManObject
{
private:
	Texture* wall = nullptr;
	Texture* food = nullptr;
	Texture * vitamin = nullptr;
	MapCell* map = nullptr;
	unsigned int rows;
	unsigned int cols;
	unsigned int totalFood = 0;

public:
	GameMap();
	//Constructora completa de un GameMap
	GameMap(unsigned int rows, unsigned int cols, Game * game);
	~GameMap();

	//Construye un GameMap a partir de un archivo
	virtual void loadFromFile(istream &archivo);
	//Guarda el mapa en un archivo proporcionado
	virtual void saveToFile(ostream &archivo);
	//Sirve para que otros elementos fuera de la classe puedan detectar si en una casilla hay un muro 
	const MapCell getCellType(unsigned int row, unsigned int col) const;
	//Establece el tipo de casilla de una posicion determinada del GameMap
	void setCellType(unsigned int row, unsigned int col, MapCell type);
	//Se encarga del dibujado especifico del GameMap
	void render();
	//Se encargade actualizar el estado del GameMap en cada vuelta del bucle principal del juego
	void update();
	bool handleEvent(SDL_Event&e);
	//Sirve para que otros elementos fuera de la classe puedan detectar el numero de filas del mapa
	const unsigned int getRows() const;
	//Sirve para que otros elementos fuera de la classe puedan detectar el numero de columnas del mapa
	const unsigned int getCols() const;
};

