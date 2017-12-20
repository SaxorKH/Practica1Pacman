#pragma once
#include "SDL.h"
#include <list>
#include "texture.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"

#define TOTAL_TEXTURAS 6
#define FRAME_RATE 150
#define TOTAL_LEVELS 2
#define VUL_TIME 10000
using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int winWidth = 500;
	unsigned int winHeight = 350;
	unsigned int cellSize = 25;
	unsigned int startTime = 0;
	unsigned int nChar;
	unsigned int rows;
	unsigned int cols;
	unsigned int points = 0;
	unsigned int currentLevel;

	bool exit = false;
	bool inicio = true;
	bool funcional;
	bool saveState = false;
	bool newLevel = true;
	bool loadState = false;
	Texture* textures = nullptr;
	list<GameCharacter*> characters;
	GameMap* gameMap = nullptr;
	const string levelPrefix = "..\\levels\\level";

	void getMapDimensions(istream & archivo);	// Obtiene las dimensiones del mapa a partir del archivo abierto previamente.
	void collision(list<GameCharacter*>::iterator ini);		// Detecta si un GameCharacter ha tocado otro, y ejecuta las 
															// respuestas necesarias.
	void SaveState();	// Le pide un código numérico al jugador y guada la partida.
	void LoadState();	// Le pide un código numérico al jugador y carga la partida.
	unsigned int GetCode(bool state);	// Lee el código numérico.
	void cleanMap();					// Vacía el mapa.
	void renderInterface();				// Renderiza la interfaz.
	void renderLetter(char l, unsigned int x, unsigned int y);	//Renderiza una letra a partir de una fuente.
	void MenuInicio();	// Ejecuta el menú de inicio.
	void saveToFile(unsigned int code); // Genera o abre el archivo de guardado a partir del código y escribe los datos de
										// la partida.
	void render();						// Renderiza la partida.
	void update();						// Actualiza el estado de la partida.
	bool loadMap(const string& filename, bool savefile = false);	// Carga un mapa de acuerdo al nombre de un archivo.
																	// Vale tanto un archivo de nivel como uno de guardado.
	void handleEvents();		// Recibe y administra los eventos del juego.
	void MenuEvents();			// Recibe y administra los eventos del menú de inicio.


public:
	Game();		// Constructor de la clase Game. Inicia SDL y crea el renderer, la ventana y las texturas.
	~Game();	// Destructor de la clase Game. Destruye el renderer, la ventana y las texturas, así como cierra SDL.
	const bool getFuncional() const;	// Devuelve un booleano que indica si el Game se ha creado correctamente.
	SDL_Renderer * getRenderer() const; // Devuelve un puntero al renderer.
	const unsigned int getCellSize() const; // Devuelve el tamaño de las celdas.
	void run();		// Ejecuta el juego.
	const bool nextCell(unsigned int x, unsigned int y, Direction dir) const;	// Lee si se puede avanzar a la celda
																				// siguiente a la posición y dirección 
																				// dadas.
	const unsigned int getRows() const;		// Devuelve las filas del mapa.
	const unsigned int getCols() const;		// Devuelve las columnas del mapa.
	void getPacmanPos(unsigned int& x, unsigned int& y);	// Escribe la posición x e y del Pacman en los atributos 
															// utilizados.
	void endGame();		// Finaliza la partida.
	void ghostScared(unsigned int energy = 0);	// Pone todos los fantasmas en estado "asustado".
	void nextLevel();	// Avanza al siguiente nivel.
	void increasePoints(unsigned int p);	// Incrementa la puntuación del jugador en la cantidad dada por el parámetro.
};

