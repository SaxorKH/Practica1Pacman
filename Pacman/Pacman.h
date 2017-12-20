#pragma once
#include "GameCharacter.h"

class Game;

using namespace std;

class Pacman : public GameCharacter
{
private:
	Direction dirbuffer = None; //Movement direction buffer
	unsigned int lives = 3; //Numberof remaining lifes
	unsigned int energy = 0;//Remaining energy
	bool hasEnergy = false;

public:
	Pacman();	// Constructor básico de Pacman.
	Pacman(Game* g);	// Constructor de Pacman con un puntero a Game.
	virtual ~Pacman();	// Destructor de Pacman.

	void update();		// Actualiza la posición del Pacman, así como su energía.
	void die();			// Pierde una vida y regresa a la posición de inicio. Si no posee vidas, se acaba el juego.
	void bufferUpdate(Direction input);	// Actualiza la dirección del Pacman recibida por las flechas de dirección.
	void startEnergy();					// Habilita el contador de la energía del Pacman mientras los fantasmas están 
										// asustados.
	void setEnergy(unsigned int en);	// Introduce la energía inicial del Pacman.
	void loadFromSavefile(istream &archivo);	// Recibe las posiciones inicial y actual, así como la dirección, del 
												// archivo. En caso de ser uno de guardado, también la energía y las
												// vidas actuales.
	void saveToFile(ostream &archivo);			// Guarda posiciones inicial y actual, dirección, energía y vidas en el
												// archivo de guardado.
	void render();								// Renderiza el Pacman y sus vidas.
};

