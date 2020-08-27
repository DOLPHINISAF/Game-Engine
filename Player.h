#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <iostream>
#include <box2d.h>

//std::string path  path to image
//w desired width in pixels
//h desired height in pixels
class Player
{
public:

	 Player(){}
	~Player(){}

	void HandleEvents();
	void Update();
	void Destroy();
	//renders the player to the screen
	void Render();

	//loads a chosen texture 
	void LoadTexture(std::string path, SDL_Renderer* renderer, b2World* world);

	void Set(int x, int y, int w, int h);
private:

	//BOX2D specs
	float density = 0.1f;
	float friction = 0.0f;
	float Ldamping = 0.0f;

	//the size of the player  | default value should be 5
	int player_scale = 5;


	bool Initialised = true;
	bool Is_moving = false;


	SDL_Texture* myTexture = NULL;
	SDL_Rect myRect;

	SDL_Renderer* renderer = NULL;




	//Animation
	const int anim_states = 7;
	int current_state = 0;
	//the rate at which the animation progresses
	int anim_multiplier = 100;
	SDL_Rect Player_current_anim[7];



	//BOX2D

	b2World* world = nullptr;

	//in pixels per second
	float max_speed = 10.f;

	b2BodyDef player_body_def;
	b2Body* player_body;
	b2PolygonShape player_shape;
	b2FixtureDef player_fixture_def;
	b2Fixture* player_fixture;

	b2Vec2 pos;

	b2MassData mass;

	b2Vec2 force;
	//the amount of force applied to the player 
	float fStrenghtX = 1000.f;

	b2Vec2 current_vel;
	b2Vec2 max_vel;

	int update_rate = 0;

};

