#pragma once
#include <fstream>
#include "Player.h"
#include "Sprite.h"

//sdl and image included in player.h
class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void HandleEvents();
	void Close();
	//logs everything to the console and to a log file
	void LOG(std::string text);
	//initialises everything
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	//return game state
	bool is_running() { return running; }

private:
	//declaring log file
	std::ofstream out;

	Player player;

	Sprite floor;

	Sprite wall;


	bool running;

	SDL_Window* gWindow = nullptr;
	SDL_Renderer* gRenderer = nullptr;


	//BOX 2D STUFF

	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 10;
	int32 positionIterations = 5;

	b2Vec2 gravity;
	
	b2World* world;
	


	

	

};

