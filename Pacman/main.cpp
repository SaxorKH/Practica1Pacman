#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
	Game game = Game();
	if (!game.getFuncional()) {
		return 1;
	}
	game.run();


	return 0;
}