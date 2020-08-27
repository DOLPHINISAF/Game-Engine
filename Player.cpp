#include "Player.h"


void Player::LoadTexture(std::string path, SDL_Renderer* renderer, b2World* world)
{
	this->renderer = renderer;
	this->world = world;

	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		std::cout << "Failed to load image at " << path.c_str() << "\n\n";
		Initialised = false;
	}
	else {
		std::cout << "Succesfully loaded image at " << path.c_str() << "\n\n";
		myTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}

	/*
	if (Initialised) {
		//idle state
		Player_current_anim[0].x = 0;
		Player_current_anim[0].y = 0;
		Player_current_anim[0].h = 16;
		Player_current_anim[0].w = 16;

		Player_current_anim[1].x = 15;
		Player_current_anim[1].y = 0;
		Player_current_anim[1].h = 16;
		Player_current_anim[1].w = 16;

		Player_current_anim[2].x = 31;
		Player_current_anim[2].y = 0;
		Player_current_anim[2].h = 16;
		Player_current_anim[2].w = 16;

		Player_current_anim[3].x = 47;
		Player_current_anim[3].y = 0;
		Player_current_anim[3].h = 16;
		Player_current_anim[3].w = 16;

		Player_current_anim[4].x = 0;
		Player_current_anim[4].y = 16;
		Player_current_anim[4].h = 16;
		Player_current_anim[4].w = 16;

		Player_current_anim[5].x = 17;
		Player_current_anim[5].y = 16;
		Player_current_anim[5].h = 16;
		Player_current_anim[5].w = 16;

		Player_current_anim[6].x = 34;
		Player_current_anim[6].y = 16;
		Player_current_anim[6].h = 16;
		Player_current_anim[6].w = 16;
	}
	*/

}

void Player::Set(int x, int y, int width, int height)
{
	myRect.x = x;
	myRect.y = y;
	myRect.w = width * player_scale;
	myRect.h = height * player_scale;


	//BOX2D

	force.SetZero();

	player_body_def.fixedRotation = true;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position.Set(float(myRect.x), float(-myRect.y));

	//creates our body
	player_body = world->CreateBody(&player_body_def);
	//sets size of shape 
	player_shape.SetAsBox(myRect.w / 2.f, myRect.h / 2.f);

	player_fixture_def.density = density;
	player_fixture_def.friction = friction;
	player_fixture_def.shape = &player_shape;
	player_body_def.linearDamping = Ldamping;
	player_fixture = player_body->CreateFixture(&player_fixture_def);

	//sets the max velocity of the player
	max_vel.x = 10.f;
	max_vel.y = 10.f;

}


void Player::Render() {
	
	myRect.x = int(pos.x) - myRect.w / 2;
	myRect.y = int(-pos.y) - myRect.h / 2;

	/*
	if (Player_current_anim && Is_moving)
	{
		myRect.w = Player_current_anim[current_state / anim_multiplier].w * player_scale;
		myRect.h = Player_current_anim[current_state / anim_multiplier].h * player_scale;
	}
	else {
		myRect.w = Player_current_anim[0].w * player_scale;
		myRect.h = Player_current_anim[0].h * player_scale;
	}
	*/
	//renders our chosen area of the texture to the screen &Player_current_anim[current_state / anim_multiplier]
	SDL_RenderCopy(renderer, myTexture, NULL, &myRect);

	pos = player_body->GetPosition();

	//if(update_rate == 0)
		//std::cout << current_vel.x << " " << current_vel.y << '\n';
}

void Player::Update() {


	current_state++;
	update_rate++;

	if (current_state >= anim_states * anim_multiplier) current_state = 1;

	
	player_body->ApplyForceToCenter(force, true);
	current_vel = player_body->GetLinearVelocity();

	//every amount of frames
	if (update_rate == 10) update_rate = 0;
}

void Player::HandleEvents() {

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_D] && current_vel.x <= max_vel.x) {
		current_vel.x = 10.f;
	}
	else if (state[SDL_SCANCODE_A] && current_vel.x >= -max_vel.x) {
		current_vel.x = -10.f;
	}
	else {
		force.x = 0.0f;
		current_vel.x = 0;
	}

	if (state[SDL_SCANCODE_W] && current_vel.y == 0) {
		current_vel.y = 50.f;
		
	}
	else {
		force.y = 0.0f;
	}
	player_body->SetLinearVelocity(current_vel);
}

void Player::Destroy() {
	SDL_DestroyTexture(myTexture);
}