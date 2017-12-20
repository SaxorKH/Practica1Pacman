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
	Pacman();	
	// Constructor básico de Pacman.
	Pacman(Game* g);
	virtual ~Pacman();

	// Actualiza la posición del Pacman, así como su energía.
	void update();		
	// Pierde una vida y regresa a la posición de inicio. Si no posee vidas, se acaba el juego.
	void die();			
	// Actualiza la dirección del Pacman recibida por las flechas de dirección.
	void bufferUpdate(Direction input);	
	// Habilita el contador de la energía del Pacman mientras los fantasmas están asustados.
	void startEnergy();					
	// Introduce la energía inicial del Pacman.
	void setEnergy(unsigned int en);	
	// Recibe las posiciones inicial y actual, así como la dirección, la energía y las vidas actuales de un archivo de
	// guardado.
	void loadFromSavefile(istream &archivo);	
	// Guarda posiciones inicial y actual, dirección, energía y vidas en el archivo de guardado.
	void saveToFile(ostream &archivo);			
	// Renderiza el Pacman y sus vidas.
	void render();								
};

