#pragma once
#include "GameState.h"
#include "GameMap.h"
#include "Pacman.h"
class PlayState :
	public GameState
{
	unsigned int winWidth = 500;
	unsigned int winHeight = 350;
	unsigned int cellSize = 25;
	unsigned int startTime = 0;
	unsigned int nChar;
	unsigned int rows;
	unsigned int cols;
	unsigned int points = 0;
	unsigned int currentLevel = 1;
	
	GameMap * map;
	Pacman * pacman;
	bool inicio = true;
	bool saveState = false;
	bool newLevel = true;
	bool load = false;
	// Obtiene las dimensiones del mapa a partir del archivo abierto previamente.
	void getMapDimensions(istream & archivo);
	// Lee un código numérico del teclado.
	unsigned int GetCode(bool state);
	// Destruye el mapa.
	void cleanMap();
	// Renderiza la interfaz.
	void renderInterface();
	//Renderiza una letra a partir de una fuente.
	void renderLetter(char l, unsigned int x, unsigned int y);
	// Recibe y gestiona los eventos del juego.
	void handleEvent();



public:
	// Carga un mapa de acuerdo al nombre de un archivo. Vale tanto un archivo de nivel como uno de guardado.
	bool loadMap(const string& filename, bool savefile = false);
	PlayState(Game * g);
	~PlayState();
	// Devuelve el tamaño de las celdas.
	const unsigned int getCellSize() const;
	// Lee si se puede avanzar a la celda siguiente a la posición y dirección dadas.
	const bool nextCell(unsigned int x, unsigned int y, Direction dir) const;
	// Devuelve las filas del mapa.
	const unsigned int getRows() const;
	// Devuelve las columnas del mapa.
	const unsigned int getCols() const;
	// Escribe la posición x e y del Pacman en los atributos utilizados.
	void getPacmanPos(unsigned int& x, unsigned int& y);
	// Finaliza la partida.
	void endGame();
	// Pone todos los fantasmas en estado "asustado".
	void ghostScared(unsigned int energy = 0);
	// Avanza al siguiente nivel.
	void nextLevel();
	// Incrementa la puntuación del jugador en la cantidad dada por el parámetro.
	void increasePoints(unsigned int p);
	void update();
	void loadSaveFile(string & s);
	void onEnter();
	// Detecta si un GameCharacter ha tocado otro, y ejecuta las respuestas necesarias.
	void collision(GameCharacter&c);
	void render();
	// Genera o abre el archivo de guardado a partir del código y escribe los datos de la partida.
	void saveToFile(unsigned int code);
};

