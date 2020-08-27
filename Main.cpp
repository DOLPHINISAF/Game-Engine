#include "Game.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
	game = new Game();

	game->Init("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	while (game->is_running()) {
		
		game->HandleEvents();
		game->Update();
		game->Render();
	}
	game->Close();

	return 0;
}