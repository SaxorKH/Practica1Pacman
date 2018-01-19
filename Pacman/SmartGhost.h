#pragma once
#include "Ghost.h"

class SmartGhost :	public Ghost
{
private:
	static const unsigned int ADULT_AGE = 100;
	static const unsigned int OLD_AGE = 200;
	unsigned int age = 0;
	//Calcula dónde dibujar el SmartGhost dependiedo del tamaño de las celdas del mapa
	SDL_Rect calcDestRect();

public:
	SmartGhost();
	//Constructor básico de SmartGhost.
	SmartGhost(Game* a); 
	//Constructor completo de SmartGhost con todos los valores necesarios.
	SmartGhost(Game * g, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir);
	~SmartGhost();

	//Actualiza el crecimiento y posición del SmartGhost de acuerdo a su edad y posición del pacman.
	void update();
	//Carga de un archivo todo lo de un GameCharacter, más la edad del SmartGhost.
	void loadFromFile(istream &archivo);
	//Guarda los mismos valores que un GameCharacter, más la edad del SmartGhost.
	void saveToFile(ostream &archivo);
	// En caso de ser viejo, da una puntuación antes de que el Game destruya el fantasma. En caso contrario hace lo mismo
	// que Ghost.
	void die();
};

