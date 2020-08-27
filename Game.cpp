#include "Game.h"

Game::Game(){
	out.open("LOG.txt");
}
Game::~Game() {

}


bool Game::Init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		LOG("SDL Initiated succesfully\n");

		gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (gWindow)
		{
			LOG("Window Initiated succesfully\n");

			gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
			if (gRenderer)
			{
				LOG("Renderer Initiated succesfully\n");
				//making the renderer white        R    G    B    ALPHA(Opacity)
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				LOG("Succesfully initiated everything\n");
			}
			else {
				LOG("Renderer failed init\n");
				return false;
			}
		}
		else
		{
			LOG("Window failed to init\n");
			return false;
		}
		
	}
	else
	{
	LOG("SDL Failed to init\n");
	return false;
	}



	running = true;
	
	//gravity specs
	gravity.Set(0.f, -9.8f);
	//sets the world gravity
	world = new b2World(gravity);


	
	//assings a texture to our player
	player.LoadTexture("images/1test.png", gRenderer, world);
	player.Set(300, 300, 16, 16);
	
	floor.LoadTexture("images/floor_sprite.png", gRenderer, world);
	floor.Set(0, 690, 30, 1280);

	wall.LoadTexture("images/floor_sprite.png", gRenderer, world);
	wall.Set(1250, 0, 720, 30);
	
	return true;
}

void Game::Render() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	//clear the screen
	SDL_RenderClear(gRenderer);
	//renders the player texture
	player.Render();
	//and the floor texture
	floor.Render(gRenderer);
	
	wall.Render(gRenderer);


	//redraw the screen
	SDL_RenderPresent(gRenderer);

}

void Game::HandleEvents()
{
	SDL_Event event;

	
	if (SDL_PollEvent(&event))
	{
		//if escape is pressed the game quits
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			running = false;
		}
			
		player.HandleEvents();
	}

	
}

void Game::Update(){
	player.Update();



	world->Step(timeStep,velocityIterations, positionIterations);
}

void Game::Close() {
	LOG("Cleaning game\n\n");

	//just destroys the textures
	player.Destroy();
	floor.Destroy();
	wall.Destroy();
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	

	SDL_Quit();

	out.close();
}
void Game::LOG(std::string text) {
	std::cout << text << '\n';
	out << text << '\n';
}

