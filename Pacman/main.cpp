#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "PacManError.h"
using namespace std;


int main(int argc, char* argv[]) {
	Game * game;
	try {
		game = new Game();
		game->run();
	}
	catch (PacManError()) {
		cout << "Finalizando programa" << endl;
	}
	return 0;
}