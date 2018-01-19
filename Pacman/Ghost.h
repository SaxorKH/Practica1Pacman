#pragma once
#include "GameCharacter.h"
class Game;

enum GhostState {
	Alive,
	Scared,
	Dead,
	Adult,
	Old
};

class Ghost : public GameCharacter
{
protected:
	static const unsigned int deadTime = 5000;
	GhostState defaultState = Alive;

	GhostState state = Alive;
	unsigned int startDeadTime = 0;

	bool sinSalida(Direction dirAux);

public:
	Ghost();
	// Constructor básico de Ghost.
	Ghost(unsigned int color, Game* a);
	//Constructor completo de Ghost con todos sus valores necesarios
	Ghost(Game * g, unsigned int col, unsigned int inix, unsigned int iniy, unsigned int x, unsigned int y, Direction dir);
	virtual ~Ghost();

	//Renderiza el fantasma en todos sus estados.
	virtual void render();
	// Actualiza la posición y el estado del fantasma.
	virtual void update();
	// Guarda las posiciones inicial y final, así como la dirección, del fantasma.
	virtual void saveToFile(ostream & archivo);
	// Cambia el estado del fantasma a Scared, determinando con la energía el tiempo restante, siendo 0 el tiempo completo.
	void scared(unsigned int energy = 0);
	// Cambia el estado del fantasma a Dead.
	virtual void die();
	// Devuelve el estado actual del Fantasma.
	GhostState getState();
	bool handleEvent(SDL_Event & e);
};

