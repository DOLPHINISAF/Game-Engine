#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <box2d.h>
class Sprite
{
public:
	void Set(int xpos, int ypos, int h, int w);
	void LoadTexture(std::string path, SDL_Renderer* renderer, b2World* world);
	void Render(SDL_Renderer* renderer);
	void Destroy();


private:
	SDL_Texture* STexture = NULL;
	SDL_Rect SRect;


	//BOX2D

	//pointer to our b2world in game.cpp
	b2World* world = nullptr;

	//creates a  ground body definition
	b2BodyDef Sbody_def;
	//creates a shape for the ground
	b2PolygonShape SBox;

	//creates a sprite body
	b2Body* SBody;

	b2Vec2 pos;

};

